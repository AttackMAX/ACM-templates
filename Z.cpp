const int P = mod;
int norm(int x)
{
    if (x < 0)
        x += P;
    if (x >= P)
        x -= P;
    return x;
}
template <class T>
T power(T a, LL b)
{
    T res = 1;
    for (; b; b /= 2, a *= a)
    {
        if (b % 2)
        {
            res *= a;
        }
    }
    return res;
}
struct Z
{
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(LL x) : x(norm(x % P)) {}
    int val() const
    {
        return x;
    }
    Z operator-() const
    {
        return Z(norm(P - x));
    }
    Z inv() const
    {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs)
    {
        x = (LL)x * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs)
    {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs)
    {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs)
    {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a)
    {
        LL v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a)
    {
        return os << a.val();
    }
};

// 加减乘除自带取模，不能用++，--

// 输出Z类变量直接用cout就行

// 配合组合数，用之前先init()

Z fac[N], invfac[N];
void init()
{
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; i++)
        fac[i] = fac[i - 1] * i;
    invfac[N - 1] = fac[N - 1].inv();
    for (int i = N - 2; i; i--)
        invfac[i] = invfac[i + 1] * (i + 1);
}

inline Z C(int a, int b)
{
    if (a < 0 || b < 0 || a < b)
        return 0;
    return fac[a] * invfac[b] * invfac[a - b];
}
