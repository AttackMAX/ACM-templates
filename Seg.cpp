struct SegmentTree
{
    struct node
    {
        int l, r;
        LL sum;
    };
    vector<int> a;
    vector<node> seg;
    SegmentTree(int n) : a(n + 1), seg(4 * n + 1) {}
    void push_up(node &x, node l, node r)
    {
        x.sum = l.sum + r.sum;
    }
    void build(int x, int l, int r)
    {
        seg[x].l = l, seg[x].r = r;
        if (l == r)
        {
            seg[x].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        push_up(seg[x], seg[x * 2], seg[x * 2 + 1]);
    }
    void modify(int x, int l, int r, LL v)
    {
        if (l > r)
            return;
        if (seg[x].l == l && seg[x].r == r)
        {
            seg[x].sum += v;
            return;
        }
        int mid = (seg[x].l + seg[x].r) >> 1;
        if (l <= mid)
            modify(x * 2, l, r, v);
        if (r > mid)
            modify(x * 2 + 1, l, r, v);
        push_up(seg[x], seg[x * 2], seg[x * 2 + 1]);
    }
    void modify(int l, int r, LL v)
    {
        modify(1, l, r, v);
    }
    node query(int x, int l, int r)
    {
        if (seg[x].l >= l && seg[x].r <= r)
            return seg[x];
        int mid = (seg[x].l + seg[x].r) >> 1;
        node ans;
        ans.sum = 0;
        if (l <= mid && r > mid)
            push_up(ans, query(2 * x, l, r), query(2 * x + 1, l, r));
        else if (l <= mid)
            ans = query(x * 2, l, r);
        else if (r > mid)
            ans = query(x * 2 + 1, l, r);
        return ans;
    }
    node query(int l, int r)
    {
        return query(1, l, r);
    }
};
