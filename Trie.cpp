struct Trie
{
    vector<vector<int>> ch;
    vector<int> cnt, sz;
    int idx = 0;
    int n;
    void init(int n)
    {
        this->n = n;
        cnt.resize(n);
        ch.resize(n, vector<int>(26));
    }
    void insert(string s)
    {
        LL u = 0;
        for (int i = 0; i < s.size(); i++)
        {
            LL v = s[i] - 'a';
            if (!ch[u][v])
                ch[u][v] = ++idx;
            u = ch[u][v];
            cnt[u]++;
        }
        sz[u]++;
    }
    LL query(string s)
    {
        LL u = 0;
        for (int i = 0; i < s.size(); i++)
        {
            LL v = s[i];
            if (!ch[u][v])
                return 0;
            u = ch[u][v];
        }
        return cnt[u];
    }
};
