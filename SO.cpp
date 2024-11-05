using db = int;                                                                           // 此处可根据题目需要改为double, longlong, 以及自定义的分数类
#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)) // 向量p1p2与p2p3的叉积
namespace SO                                                                              // 斜率优化
{
    // X(j)单调性、求解的时max还是min; 1表示单增/max(上凸壳)，0表示单减/min(下凸壳)
    const bool dx = 1, dm = 0;
    const int initClock()
    {           // 凸壳旋转的方向，取决于x的单调性和维护的上/下凸壳（最大/小值）
        if (dm) // 上凸壳
            return !dx;
        else // 下凸壳
            return dx;
    }
    const bool dc = initClock(); // 凸壳旋转的方向，1表示逆时针，0表示顺时针

    db dp[N];
    struct P
    {
        db x, y;
        P() {}
        P(db x, db y) : x(x), y(y) {}
        P operator-(P p) { return {x - p.x, y - p.y}; }
        db det(P p) { return x * p.y - y * p.x; } // 叉积
    };
    deque<P> Q;

    // Y(j) = K(i)X(j) + B(i), B(i) = dp[i] + A(i)
    db K(int i) { return /* ... */; }
    db X(int j) { return /* ... */; }
    db Y(int j) { return /* ... */; }
    db A(int i) { return /* ... */; }
    db B(int i) { return Q.front().y - K(i) * Q.front().x; }

    bool checkBack(P &p)
    {           //  跟原本凸包旋转方向相反，则是上/下凸点
        if (dc) // 逆时针
            return cross(Q[Q.size() - 2], Q.back(), p) <= 0;
        else // 顺时针
            return cross(Q[Q.size() - 2], Q.back(), p) >= 0;
    }

    void update(int i)
    {
        P p(X(i), Y(i));
        while (Q.size() >= 2 && checkBack(p))
            Q.pop_back();
        Q.push_back(p);
    }

    bool checkFront(P &k)
    {                                       // k转到头部向量，和原本凸包旋转方向相反
        if (dc)                             // 逆时针
            return k.det(Q[1] - Q[0]) <= 0; // 叉积为负，则是顺时针
        else                                // 顺时针
            return k.det(Q[1] - Q[0]) >= 0;
    }

    db query(int i)
    {
        P k(1, K(i)); // 斜率对应的向量
        while (Q.size() >= 2 && checkFront(k))
            Q.pop_front();
        return B(i) - A(i);
    }

    db run(int n)
    {
        update(0);
        for (int i = 1; i <= n; i++)
        {
            dp[i] = query(i);
            update(i);
        }
        return dp[n];
    }
}