#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;

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
        double dis() const { return sqrt((double)dis2()); }
        T dot(P p) const { return x * p.x + y * p.y; }
        T cross(P p) const { return x * p.y - y * p.x; }
        P perp() const { return { -y, x }; } // +90 deg
    };

    template <typename P>
    auto dot(P a, P b) { return a.x * b.x + a.y + b.y; }

    template <typename P>
    auto cross(P a, P b) { return a.x * b.y - a.y * b.x; }

    using Point = PointBase<ll>;
    constexpr double eps = 1e-10;

    vector<Point> getConvexHull(vector<Point> poly)
    {
        // line 위 포함 => while 안 cross 등호 빼고, 일자인 경우 예외처리
        if(poly.size() <= 1) return poly;
        sort(poly.begin(), poly.end());

        vector<Point> lo;
        for(int i = 0; i < poly.size(); ++i) {
            int sz = lo.size();
            auto p = poly[i];
            while(sz >= 2 && cross(lo[sz - 1] - lo[sz - 2], p - lo[sz - 2]) <= 0) {
                lo.pop_back();
                sz--;
            }
            lo.push_back(p);
        }
        vector<Point> hi;
        for(int i = poly.size() - 1; i >= 0; --i) {
            int sz = hi.size();
            auto p = poly[i];
            while(sz >= 2 && cross(hi[sz - 1] - hi[sz - 2], p - hi[sz - 2]) <= 0) {
                hi.pop_back();
                sz--;
            }
            hi.push_back(p);
        }

        lo.insert(lo.end(), hi.begin() + 1, hi.end() - 1);
        return lo;
    }
}


void solve()
{
    using namespace geo;
    vector<Point> d(4);
    for(auto& v : d)cin >> v.x >> v.y;
    auto res = getConvexHull(d);
    if(res.size() == 4) cout << "Yes";
    else cout << "No";
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
