struct DSU
{
    vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { iota(f.begin(), f.end(), 0); }
    int find(int x)
    {
        if (x == f[x])
            return x;
        else
        {
            f[x] = find(f[x]); // 父节点设为根节点
            return f[x];       // 返回父节点
        }
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};

// siz[x]：存x的儿子个数(包括自己)
// f[x]：存x的父亲

// DSU dsu(n);  //构造大小为n个点的dsu，点值为[0,n-1]
// dsu.find(i);  //找i点的祖先
// dsu.merge(x,y);  //合并x,y
// dsu.size(x); //返回x所在家族的大小
