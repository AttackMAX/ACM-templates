int id = 1;

struct PresidentTree
{
    struct node
    {
        int l, r, val;
    };
    vector<node> seg;
    PresidentTree(int n) : seg(n * 4 + 17 * n) {}
    void build(int version, int l, int r)
    {
        if (l == r)
        {
            seg[version].val = 0;
            return;
        }
        int mid = (l + r) >> 1;
        seg[version].l = ++id, seg[version].r = ++id;
        build(seg[version].l, l, mid);
        build(seg[version].r, mid + 1, r);

        seg[version].val = seg[seg[version].l].val + seg[seg[version].r].val;
    }

    void modify(int last, int now, int l, int r, int pos, int val)
    {
        if (l == r)
        {
            seg[now].val = seg[last].val + val;
            return;
        }
        int mid = (l + r) >> 1;
        seg[now].l = seg[last].l, seg[now].r = seg[last].r;
        if (pos <= mid)
        {
            seg[now].l = ++id;
            modify(seg[last].l, seg[now].l, l, mid, pos, val);
        }
        else
        {
            seg[now].r = ++id;
            modify(seg[last].r, seg[now].r, mid + 1, r, pos, val);
        }

        seg[now].val = seg[seg[now].l].val + seg[seg[now].r].val;
    }

    int query(int last, int now, int l, int r, int k)
    {
        if (l == r)
            return l;

        int mid = (l + r) >> 1, d = seg[seg[now].l].val - seg[seg[last].l].val;
        if (d < k)
            return query(seg[last].r, seg[now].r, mid + 1, r, k - d);
        else
            return query(seg[last].l, seg[now].l, l, mid, k);
    }
};
