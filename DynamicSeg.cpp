struct DynamicSeg
{
    struct node
    {
        int l = 0, r = 0;
        LL sum = 0;
        node() : l(0), r(0), sum(0) {}
    };
    int idx, MIN, MAX, mx, n;
    vector<node> seg;
    DynamicSeg(int _n, LL Min, LL Max) : n(_n), idx(0), MIN(Min), MAX(Max)
    {
        seg.resize(2 * n * ((int)log2(n) + 1));
    }
    void push_up(node &x, node l, node r)
    {
        x.sum = l.sum + r.sum;
    }
    void modify(int &x, int l, int r, int pos, LL val)
    {
        if (x == 0)
            x = ++idx;
        if (l == r)
        {
            seg[x].sum += val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            modify(seg[x].l, l, mid, pos, val);
        else
            modify(seg[x].r, mid + 1, r, pos, val);
        push_up(seg[x], seg[seg[x].l], seg[seg[x].r]);
    }
    void modify(int &x, int pos, LL val)
    {
        modify(x, MIN, MAX, pos, val);
    }
    node query(int x, int l, int r, int L, int R)
    {
        if (x == 0 || R < l || L > r)
            return node();
        if (L <= l && R >= r)
            return seg[x];
        int mid = (l + r) >> 1;
        node ans;
        ans.sum = 0;
        if (L <= mid && R > mid)
            push_up(ans, query(seg[x].l, l, mid, L, R), query(seg[x].r, mid + 1, r, L, R));
        else if (L <= mid)
            ans = query(seg[x].l, l, mid, L, R);
        else if (R > mid)
            ans = query(seg[x].r, mid + 1, r, L, R);
        return ans;
    }
    node query(int l, int r)
    {
        return query(1, MIN, MAX, l, r);
    }
    // 线段树合并使用
    //  int merge(int rt1,int rt2,int l,int r){
    //  	if(rt1 == 0 || rt2 == 0) return rt1 + rt2;
    //  	if(l == r){
    //  		seg[rt1].sum += seg[rt2].sum;
    //  		return rt1;
    //  	}
    //  	int mid = (l + r) >> 1;
    //  	seg[rt1].l = merge(seg[rt1].l,seg[rt2].l.l,mid);
    //  	seg[rt1].r = merge(seg[rt1].r,seg[rt2].r,mid + 1,r);
    //  	push_up(seg[rt1],seg[seg[rt1].l],seg[seg[rt2].r]);
    //  }
    //  int merge(int rt1,int rt2){
    //  	return merge(rt1,rt2,MIN,MAX);
    //  }
};
