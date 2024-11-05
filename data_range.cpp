#include <bits/stdc++.h>
using namespace std;
#define LL long long

mt19937 rnd(chrono::steady_clock().now().time_since_epoch().count());
int rng(int l, int r)
{ // [l, r]
    return rnd() % (r - l + 1) + l;
}

void array(int n)
{                // 生成一个n大小的数组
    int m = 1E9; // m为数据范围
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = rng(0, m);
        cout << a[i] << " \n"[i == n - 1];
    }
}

void cand(int m, int n)
{ // n生成m个区间，每个区间两端点大小为[1,n]
    for (int i = 0; i < m; i++)
    {
        int l = rng(1, n);
        int r = rng(1, n);
        if (l > r)
        {
            swap(l, r);
        }
        cout << l << " " << r << "\n";
    }
}

void tree(int n)
{                // 生成一个n个点的树
    int m = 1E9; // m为树的边权范围
    for (int i = 1; i < n; i++)
    {
        int p = rng(0, i - 1);
        int v = rng(1, m); // v为边权
        cout << p + 1 << " " << i + 1 << " " << v << "\n";
    }
}

void graph(int n, int m)
{ // 生成一个n个点m条边的无向图，无重边和自环且一定联通。
    vector<pair<int, int>> e;
    map<pair<int, int>, bool> f;
    cout << n << " " << m << "\n";

    for (int i = 1; i < n; i++)
    {
        int p = rng(0, i - 1);
        e.push_back(make_pair(p, i));
        f[make_pair(p, i)] = f[make_pair(i, p)] = true;
    }
    for (int i = n; i <= m; i++)
    {
        int x, y;
        do
        {
            x = rng(0, n - 1);
            y = rng(0, n - 1);
        } while (x == y || f.count(make_pair(x, y)));

        e.push_back(make_pair(x, y));
        f[make_pair(x, y)] = f[make_pair(y, x)] = true;
    }

    shuffle(e.begin(), e.end(), rnd);

    for (auto [x, y] : e)
    {
        cout << x + 1 << " " << y + 1 << "\n";
    }
}

signed main()
{
    int T = 5;
    cout << T << "\n";
    while (T--)
    {
        graph(3, 3);
    }
    return 0;
}