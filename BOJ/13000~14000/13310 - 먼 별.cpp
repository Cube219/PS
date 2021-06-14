#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

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

ll lensq(Point& a, Point& b)
{
    ll dx = abs(a.x - b.x);
    ll dy = abs(a.y - b.y);
    return dx * dx + dy * dy;
}

void convexHull(vector<Point>& p, vector<Point>& st, bool erase = false)
{
    if(p.size() <= 2) {
        st.assign(p.begin(), p.end());
        if(erase == true) p.clear();
        return;
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
    st.push_back(pivot);
    st.push_back(p[0]);
    vector<int> eraseIdx;
    eraseIdx.push_back(0);
    for(int i = 1; i < p.size(); ++i) {
        if(st.size() < 2) {
            st.push_back(p[i]);
            eraseIdx.push_back(i);
            continue;
        }
        Point p2 = p[i];
        Point p1 = st[st.size() - 1];
        Point p0 = st[st.size() - 2];

        Point l1 = p1 - p0;
        Point l2 = p2 - p0;
        ll cw = ccw(l1, l2);
        if(cw > 0) {
            st.push_back(p[i]);
            eraseIdx.push_back(i);
        } else {
            st.pop_back();
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
}

ll rotatingCalipers(vector<Point>& cvh)
{
    ll res = 0;
    int cvhn = cvh.size();

    int aidx = 0, bidx = 0;
    for(int i = 1; i < cvhn; ++i) {
        ll l = lensq(cvh[0], cvh[i]);
        if(res < l) {
            res = l;
            bidx = i;
        }
    }
    for(int i = 0; i < cvhn; ++i) {
        ll l = lensq(cvh[aidx], cvh[bidx]);
        if(res < l) {
            res = l;
        }
        Point av = cvh[(aidx + 1) % cvhn] - cvh[aidx];
        Point bv = cvh[(bidx + 1) % cvhn] - cvh[bidx];
        bv.x = -bv.x;
        bv.y = -bv.y;
        if(ccw(av, bv) > 0) {
            aidx++;
            aidx %= cvhn;
        } else {
            bidx++;
            bidx %= cvhn;
        }
    }

    return res;
}

int n, t;
Point d[30001], v[30001];
vector<Point> d2, cv;

ll tfunc(ll x)
{
    d2.clear();
    cv.clear();
    for(int i = 0; i < n; ++i) {
        d2.push_back({ d[i].x + v[i].x * x, d[i].y + v[i].y * x });
    }
    convexHull(d2, cv);

    return rotatingCalipers(cv);
}

pair<int, ll> tsearch(ll minv, ll maxv)
{
    ll l = minv, r = maxv;
    while(l + 2 < r) {
        ll p = (l * 2 + r) / 3;
        ll q = (l + r * 2) / 3;

        ll pv = tfunc(p);
        ll qv = tfunc(q);
        if(pv <= qv) r = q;
        else l = p;
    }
    
    ll res = tfunc(l);
    int idx = l;
    for(ll i = l + 1; i <= r; ++i) {
        ll v = tfunc(i);
        if(res > v) {
            res = v;
            idx = i;
        }
    }
    return { idx, res };
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y >> v[i].x >> v[i].y;
    }

    auto res = tsearch(0, t);
    cout << res.first << "\n" << res.second;

    return 0;
}
