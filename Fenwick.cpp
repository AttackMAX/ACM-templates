struct Fenwick
{
    int n;
    vector<T> a;
    Fenwick(int n = 0) { init(n); }
    void init(int n)
    {
        this->n = n;
        a.assign(n, T());
    }
    // 在x处加上v
    void add(int x, T v)
    {
        for (int i = x + 1; i <= n; i += i & -i)
        {
            a[i - 1] += v;
        }
    }
    // 取[0.x)的和
    T sum(int x)
    {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i)
        {
            ans += a[i - 1];
        }
        return ans;
    }
    // 取[l,r)的和
    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l);
    }
    // 取已插入的元素从小到大排序后第k个元素的值，这里从0开始记录
    int kth(T k)
    {
        int x = 0;
        for (int i = 1 << __lg(n); i; i /= 2)
        {
            if (x + i <= n && k >= a[x + i - 1])
            {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

// Fenwick<int> fen(N);
// fen.add(x,y);   //往x位置加上y
// fen.sum(x+1);   //求[0,x+1)的和
