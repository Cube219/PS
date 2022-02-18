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
    bool isWall;
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

vector<Point> convexHull(vector<Point>& p, bool erase = false)
{
    vector<Point> res;
    if(p.size() <= 2) {
        res.assign(p.begin(), p.end());
        if(erase == true) p.clear();
        return res;
    }

    sort(p.begin(), p.end(), [](const Point& l, const Point& r) {
        if(l.y == r.y) return l.x > r.x;
        return l.y > r.y;
    });
    Point pivot = p.back();
    p.pop_back();
    sort(p.begin(), p.end(), [pivot](const Point& l, const Point& r) {
        Point l1 = l - pivot;
        Point l2 = r - pivot;
        ll cw = ccw(l1, l2);
        if(cw == 0) {
            if(l1.y == l2.y) return l1.x < l2.x;
            return l1.y < l2.y;
        } else if(cw > 0) return true;
        else return false;
    });
    int idx = p.size() - 1;
    Point t1 = p[idx] - pivot;
    while(idx > 0) {
        Point t2 = p[idx] - pivot;
        if(ccw(t1, t2) != 0) {
            idx++;
            break;
        }
        idx--;
    }
    reverse(p.begin() + idx, p.end());

    res.push_back(pivot);
    res.push_back(p[0]);
    vector<int> eraseIdx;
    eraseIdx.push_back(0);
    for(int i = 1; i < p.size(); ++i) {
        if(res.size() < 2) {
            res.push_back(p[i]);
            eraseIdx.push_back(i);
            continue;
        }
        Point p2 = p[i];
        Point p1 = res[res.size() - 1];
        Point p0 = res[res.size() - 2];

        Point l1 = p1 - p0;
        Point l2 = p2 - p0;
        ll cw = ccw(l1, l2);
        if(cw >= 0) {
            res.push_back(p[i]);
            eraseIdx.push_back(i);
        } else {
            res.pop_back();
            eraseIdx.pop_back();
            i--;
        }
    }
    if(erase == true) {
        sort(eraseIdx.begin(), eraseIdx.end());
        eraseIdx.push_back(-1);
        int ei = 0;
        vector<Point> newp;
        for(int i = 0; i < p.size(); ++i) {
            if(i == eraseIdx[ei]) {
                ei++;
            } else {
                newp.push_back(p[i]);
            }
        }
        p.clear();
        p.assign(newp.begin(), newp.end());
    } else {
        p.push_back(pivot);
    }

    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<Point> d;
    for(int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        d.push_back({ x, y, true });
    }
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        d.push_back({ x, y, false });
    }

    auto cv = convexHull(d);

    int res = 0;
    for(int i = 0; i < (int)cv.size() - 1; ++i) {
        if(cv[i].isWall && cv[i + 1].isWall) res++;
    }
    if(cv.size() >= 2 && cv[0].isWall && cv.back().isWall) res++;
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
