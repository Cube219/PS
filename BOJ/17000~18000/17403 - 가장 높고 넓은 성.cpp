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
    int idx = 0;
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

int n;
Point d[1001];
vector<Point> cur, c2, nxt;
int res[1001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cur.resize(n);
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        d[i] = { a, b, i };
        cur[i] = d[i];
    }

    for(int cnt = 1; cnt < 10000; ++cnt) {
        c2.clear();
        convexHull(cur, c2, true);
        if(c2.size() <= 2) break;

        for(int i = 0; i < c2.size(); ++i) {
            res[c2[i].idx] = cnt;
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
