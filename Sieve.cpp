// minp存这个数的最小质数
// primes存质数
vector<int> minp, primes;
void sieve(int n)
{
    minp.assign(n + 1, 0);
    primes.clear();
    for (int i = 2; i <= n; i++)
    {
        if (minp[i] == 0)
        {
            minp[i] = i;
            primes.push_back(i);
        }
        for (auto p : primes)
        {
            if (i * p > n)
                break;
            minp[i * p] = p;
            if (p == minp[i])
                break;
        }
    }
}

// sieve(1e6);  //算出[0,1e6]内的质数
// minp[4]=2;
// primes[2]=5;
