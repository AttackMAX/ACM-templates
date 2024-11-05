set<PII> E;

struct EBCC
{
    int n;
    vector<vector<int>> adj;
    vector<int> stk;
    vector<int> dfn, low, bel;
    int cur, cnt;

    EBCC() {}
    EBCC(int n)
    {
        init(n);
    }

    void init(int n)
    {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    // 插边
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x, int p)
    {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);

        for (auto y : adj[x])
        {
            if (y == p)
            {
                continue;
            }
            if (dfn[y] == -1)
            {
                E.emplace(x, y);
                dfs(y, x);
                low[x] = min(low[x], low[y]);
            }
            else if (bel[y] == -1 && dfn[y] < dfn[x])
            {
                E.emplace(x, y);
                low[x] = min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x])
        {
            int y;
            do
            {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    // 执行主体,返回bel,bel[u]指u点缩点后是哪个点
    vector<int> work()
    {
        dfs(1, -1);
        return bel;
    }

    struct Graph
    {
        // 缩点后的点数,缩点后的边数
        int n;
        vector<PII> edges;
        // 缩点的点包含原先的点数
        vector<int> siz;
        // 缩点的点包含的原先的边边+该点到其儿子的边数 的个数
        // 父亲和儿子由dfn序决定
        vector<int> cnte;
    };
    // 缩点,先执行work,返回缩点后的图的信息,信息内容如Graph注释
    Graph compress()
    {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int i = 1; i < n; i++)
        {
            g.siz[bel[i]]++;
            for (auto j : adj[i])
            {
                if (bel[i] < bel[j])
                {
                    g.edges.emplace_back(bel[i], bel[j]);
                }
                else if (i < j)
                {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};

// EBCC g(n); //建EBCC
// for(int i=1;i<=m;i++){
//     int u,v;
//     cin>>u>>v;
//     g.addEdge(u,v);  //加边
// }
// auto res=g.work();  //执行EBCC割边,返回各点缩点后的对应的点
// auto [ng,edges,siz,cnte]=g.compress(); //获取割边缩点后的图的信息

// //建立割边缩点后的图
// vector<vector<int>>adj(ng + 1);
// for(auto &[u,v]:edges){
//     adj[u].push_back(v);
//     adj[v].push_back(u);
// }

// //输出一种无向边改有向边的方式,使得更改后满足:整个图是强连通的
// for(auto[x,y]:E) {
//     cout<<x<<" "<<y<<"\n";
// }
