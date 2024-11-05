struct Shash
{
    const LL base[2] = {29, 31};
    const LL hashmod[2] = {(LL)1e9 + 9, 998244353};

    array<vector<LL>, 2> hsh;
    array<vector<LL>, 2> pwMod;
    void init(string S)
    {
        int n = S.size();
        S = ' ' + S;
        hsh[0].resize(n + 1), hsh[1].resize(n + 1);
        pwMod[0].resize(n + 1), pwMod[1].resize(n + 1);
        for (int i = 0; i < 2; i++)
        {
            pwMod[i][0] = 1;
            for (int j = 1; j <= n; j++)
            {
                pwMod[i][j] = pwMod[i][j - 1] * base[i] % hashmod[i];
                hsh[i][j] = (hsh[i][j - 1] * base[i] + S[j]) % hashmod[i];
            }
        }
    }
    pair<LL, LL> get(int l, int r)
    {
        pair<LL, LL> ans;
        ans.first = (hsh[0][r] - hsh[0][l - 1] * pwMod[0][r - l + 1]) % hashmod[0];
        ans.second = (hsh[1][r] - hsh[1][l - 1] * pwMod[1][r - l + 1]) % hashmod[1];
        ans.first = (ans.first + hashmod[0]) % hashmod[0];
        ans.second = (ans.second + hashmod[1]) % hashmod[1];
        return ans;
    }
};
bool same(Shash &a, int la, int ra, Shash &b, int lb, int rb)
{
    return a.get(la, ra) == b.get(lb, rb);
}
