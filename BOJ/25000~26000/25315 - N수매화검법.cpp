#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct Point
{
    ll x, y;
};

Point operator+(const Point& l, const Point& r)
{
    return { l.x + r.x, l.y + r.y };
}

Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}

ll dot(const Point& l, const Point& r)
{
    return l.x * r.x + l.y * r.y;
}

ll ccw(Point l1, Point l2)
{
    return l1.x * l2.y - l2.x * l1.y;
}

ll lensq(const Point& a, const Point& b)
{
    ll dx = abs(a.x - b.x);
    ll dy = abs(a.y - b.y);
    return dx * dx + dy * dy;
}

bool isCross(Point l1p1, Point l1p2, Point l2p1, Point l2p2)
{
    Point line = l1p2 - l1p1;
    Point a = l2p1 - l1p2;
    Point b = l2p2 - l1p2;
    ll cwa = ccw(line, a);
    ll cwb = ccw(line, b);
    if((cwa > 0 && cwb > 0) || (cwa < 0 && cwb < 0)) return false;
    if(cwa == 0 && cwb == 0) {
        if(l1p1.x > l1p2.x) swap(l1p1.x, l1p2.x);
        if(l1p1.y > l1p2.y) swap(l1p1.y, l1p2.y);
        if(l2p1.x > l2p2.x) swap(l2p1.x, l2p2.x);
        if(l2p1.y > l2p2.y) swap(l2p1.y, l2p2.y);

        if(l1p2.x < l2p1.x) return false;
        if(l2p2.x < l1p1.x) return false;
        if(l1p2.y < l2p1.y) return false;
        if(l2p2.y < l1p1.y) return false;

        return true;
    }

    line = l2p2 - l2p1;
    a = l1p1 - l2p2;
    b = l1p2 - l2p2;
    cwa = ccw(line, a);
    cwb = ccw(line, b);
    if((cwa > 0 && cwb > 0) || (cwa < 0 && cwb < 0)) return false;
    return true;
}

void solve()
{
    int n;
    cin >> n;
    struct Node
    {
        Point s, e;
        ll w;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.s.x >> v.s.y >> v.e.x >> v.e.y >> v.w;

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.w < r.w;
    });

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        int num = 1;
        for(int j = i + 1; j < n; ++j) {
            if(isCross(d[i].s, d[i].e, d[j].s, d[j].e)) {
                num++;
            }
        }
        res += num * d[i].w;
    }
    cout << res;
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
