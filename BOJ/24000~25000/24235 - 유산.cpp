#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
using ld = long double;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

// https://github.com/kth-competitive-programming/kactl/tree/main/content/geometry
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<long double> P;
vector<P> convexHull(vector<P> pts)
{
    if(sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<P> h(sz(pts) + 1);
    int s = 0, t = 0;
    for(int it = 2; it--; s = --t, reverse(all(pts)))
        for(P p : pts) {
            while(t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
            h[t++] = p;
        }
    return { h.begin(), h.begin() + t - (t == 2 && h[0] == h[1]) };
}

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2)
{
    auto d = (e1 - s1).cross(e2 - s2);
    if(d == 0) // if parallel
        return { -(s1.cross(e1, s2) == 0), P(0, 0) };
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return { 1, (s1 * p + e1 * q) / d };
}

vector<P> polygonCut(const vector<P>& poly, P s, P e)
{
    vector<P> res;
    rep(i, 0, sz(poly))
    {
        P cur = poly[i], prev = i ? poly[i - 1] : poly.back();
        bool side = s.cross(e, cur) < 0;
        if(side != (s.cross(e, prev) < 0))
            res.push_back(lineInter(s, e, cur, prev).second);
        if(side)
            res.push_back(cur);
    }
    return res;
}

template<class T>
T polygonArea2(vector<Point<T>>& v)
{
    T a = v.back().cross(v[0]);
    rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
    return a;
}


void solve()
{
    int n;
    cin >> n;
    vector<P> ori(n);
    ld mn = LNF, mx = -LNF;
    ld mny = LNF, mxy = -LNF;
    for(auto& v : ori) {
        cin >> v.x >> v.y;
        mn = min(mn, v.x);
        mx = max(mx, v.x);

        mny = min(mny, v.y);
        mxy = max(mxy, v.y);
    }

    auto cvx = convexHull(ori);
    ld inita = polygonArea2(cvx);

    // 클 경우 true
    auto ck = [&](long double k) -> bool {
        P p0(k, (ld)mny - 1);
        P p1(k, (ld)mxy + 1);

        auto cut = polygonCut(cvx, p0, p1);

        ld area = polygonArea2(cut);

        if(area < inita / 2) return true;
        else return false;
    };

    long double lo = mn, hi = mx;
    while(hi - lo > 1e-4) {
        long double m = (lo + hi) / 2.0;
        if(ck(m)) {
            hi = m;
        } else {
            lo = m;
        }
    }
    cout << fixed << setprecision(15) << lo;
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
