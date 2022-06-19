#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

namespace geo
{
    template <typename T>
    struct PointBase
    {
        using P = PointBase;

        T x, y;
        PointBase(T _x = 0, T _y = 0) : x(_x), y(_y) {}

        P operator+(P p) const { return { x + p.x, y + p.y }; }
        P operator-(P p) const { return { x - p.x, y - p.y }; }
        P operator*(T d) const { return { x * d, y * d }; }
        P operator/(T d) const { return { x / d, y / d }; }

        bool operator<(const P& rhs) const { return tie(x, y) < tie(rhs.x, rhs.y); }
        bool operator==(const P& rhs) const { return tie(x, y) == tie(rhs.x, rhs.y); }

        T dis2() const { return x * x + y * y; }
        long double dis() const { return sqrt((long double)dis2()); }
        T dot(P p) const { return x * p.x + y * p.y; }
        T cross(P p) const { return x * p.y - y * p.x; }
        P perp() const { return { -y, x }; } // +90 deg
    };

    template <typename P>
    auto dot(P a, P b) { return a.x * b.x + a.y + b.y; }

    template <typename P>
    auto cross(P a, P b) { return a.x * b.y - a.y * b.x; }

    using Point = PointBase<long double>;
}

constexpr long double PI = 3.141592653589793238;

void solve()
{
    geo::Point src, dst, red, blue;
    long double redR, blueR;
    cin >> src.x >> src.y;
    cin >> dst.x >> dst.y;
    cin >> blue.x >> blue.y >> blueR;
    cin >> red.x >> red.y >> redR;

    long double disSrc, disDst, dx, dy;
    long double srcA, dstA, a;

    dx = src.x - red.x;
    dy = src.y - red.y;
    disSrc = sqrt(dx * dx + dy * dy);
    srcA = acos(redR / disSrc);

    dx = dst.x - red.x;
    dy = dst.y - red.y;
    disDst = sqrt(dx * dx + dy * dy);
    dstA = acos(redR / disDst);

    long double disSD;
    dx = src.x - dst.x;
    dy = src.y - dst.y;
    disSD = sqrt(dx * dx + dy * dy);

    a = acos((disSrc * disSrc + disDst * disDst - disSD * disSD) / (2 * disSrc * disDst));

    a -= srcA;
    a -= dstA;

    long double res = a * redR + sqrt(disSrc * disSrc - redR * redR) + sqrt(disDst * disDst - redR * redR);
    cout << fixed << setprecision(15) << res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
