struct ST
{
    int n;
    vector<int> in1, in2, lg;
    vector<vector<int>> Max, Min;
    ST(int n) : n(n), in1(n + 1), in2(n + 1), lg(n + 1)
    {
        for (int i = 2; i <= n; i++)
        {
            lg[i] = lg[i / 2] + 1;
        }
        Max.resize(n + 1, vector<int>(lg[n] + 1));
        Min.resize(n + 1, vector<int>(lg[n] + 1));
    }
    void init()
    {
        for (int i = 1; i <= n; i++)
        {
            Max[i][0] = in1[i];
            Min[i][0] = in2[i];
        }
        int k = lg[n];
        for (int j = 1; j <= k; j++)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                Max[i][j] = max(Max[i][j - 1], Max[i + (1 << (j - 1))][j - 1]);
                Min[i][j] = min(Min[i][j - 1], Min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int getMax(int l, int r)
    {
        if (l > r)
        {
            swap(l, r);
        }
        int k = lg[r - l + 1];
        return max(Max[l][k], Max[r - (1 << k) + 1][k]);
    }
    int getMin(int l, int r)
    {
        if (l > r)
        {
            swap(l, r);
        }
        int k = lg[r - l + 1];
        return min(Min[l][k], Min[r - (1 << k) + 1][k]);
    }
};
