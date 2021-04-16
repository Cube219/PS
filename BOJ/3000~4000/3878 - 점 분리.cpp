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
Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x,l.y - r.y };
}

ll ccw(Point l1, Point l2)
{
    return l1.x * l2.y - l2.x * l1.y;
}

int tNum;
int n, m;
vector<Point> bp, wp;
vector<Point> bst, wst;

void p(vector<Point>& p, vector<Point>& st)
{
    if(p.size() <= 2) {
        st.assign(p.begin(), p.end());
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
    for(int i = 1; i < p.size(); ++i) {
        if(st.size() < 2) {
            st.push_back(p[i]);
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
        } else {
            st.pop_back();
            i--;
        }
    }
    p.push_back(pivot);
}

struct Line
{
    ll x1;
    ll y1;
    ll x2;
    ll y2;
};

bool isCross(Line l1, Line l2)
{
    ll vx = l1.x2 - l1.x1;
    ll vy = l1.y2 - l1.y1;

    ll ax = l2.x1 - l1.x2;
    ll ay = l2.y1 - l1.y2;
    ll bx = l2.x2 - l1.x2;
    ll by = l2.y2 - l1.y2;

    ll ccwa = ccw({ vx, vy }, { ax, ay });
    ll ccwb = ccw({ vx, vy }, { bx, by });
    if((ccwa > 0 && ccwb > 0) || (ccwa < 0 && ccwb < 0)) return false;
    if(ccwa == 0 && ccwb == 0) {
        if(l1.x1 > l1.x2) swap(l1.x1, l1.x2);
        if(l1.y1 > l1.y2) swap(l1.y1, l1.y2);
        if(l2.x1 > l2.x2) swap(l2.x1, l2.x2);
        if(l2.y1 > l2.y2) swap(l2.y1, l2.y2);

        if(l1.x2 < l2.x1) return false;
        if(l2.x2 < l1.x1) return false;
        if(l1.y2 < l2.y1) return false;
        if(l2.y2 < l1.y1) return false;

        return true;
    }

    vx = l2.x2 - l2.x1;
    vy = l2.y2 - l2.y1;

    ax = l1.x1 - l2.x2;
    ay = l1.y1 - l2.y2;
    bx = l1.x2 - l2.x2;
    by = l1.y2 - l2.y2;

    ccwa = ccw({ vx, vy }, { ax, ay });
    ccwb = ccw({ vx, vy }, { bx, by });
    if((ccwa > 0 && ccwb > 0) || (ccwa < 0 && ccwb < 0)) return false;

    return true;
}

bool isinline(Point lp1, Point lp2, Point p);
bool isin(vector<Point>& pol, Point p)
{
    for(int i = 1; i < pol.size(); ++i) {
        Point cur = pol[i - 1];
        Point nxt = pol[i];
        Point l1 = nxt - cur;
        Point l2 = p - cur;
        ll cw = ccw(l1, l2);
        if(cw == 0) {
            if(isinline(nxt, cur, p) == true) return true;
            else return false;
        } else if(cw < 0) {
            return false;
        }
    }

    return true;
}

bool isinline(Point lp1, Point lp2, Point p)
{
    Point l1 = lp2 - lp1;
    Point l2 = p - lp1;
    ll cw = ccw(l1, l2);
    if(cw != 0) return false;
    else {
        ll dt, dt2;
        if(lp1.x == lp2.x) {
            dt = abs(lp1.y - lp2.y);
            dt2 = max(abs(p.y - lp1.y), abs(p.y - lp2.y));
        } else {
            dt = abs(lp1.x - lp2.x);
            dt2 = max(abs(p.x - lp1.x), abs(p.x - lp2.x));
        }
        if(dt < dt2) return false;
        else return true;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        bp.clear(); wp.clear();
        bst.clear(); wst.clear();
        cin >> n >> m;
        bp.resize(n); wp.resize(m);
        for(int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            bp[i] = { a, b };
        }
        for(int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            wp[i] = { a, b };
        }
        p(bp, bst);
        p(wp, wst);

        bool pos = true;
        if(bst.size() == 1 && wst.size() == 1) {
            pos = true;
        } else if(bst.size() == 1 && wst.size() == 2) {
            if(isinline(wst[0], wst[1], bst[0]) == true) pos = false;
        } else if(bst.size() == 2 && wst.size() == 1) {
            if(isinline(bst[0], bst[1], wst[0]) == true) pos = false;
        } else if(bst.size() == 2 && wst.size() == 2) {
            Line l1 = { bst[0].x, bst[0].y, bst[1].x, bst[1].y };
            Line l2 = { wst[0].x, wst[0].y, wst[1].x, wst[1].y };
            if(isCross(l1, l2) == true) pos = false;
        } else {
            bst.push_back(bst[0]);
            wst.push_back(wst[0]);
            if(bst.size() > 2) {
                for(int i = 0; i < wp.size(); ++i) {
                    if(isin(bst, wp[i]) == true) {
                        pos = false;
                        break;
                    }
                }
            }
            if(wst.size() > 2) {
                for(int i = 0; i < bp.size(); ++i) {
                    if(isin(wst, bp[i]) == true) {
                        pos = false;
                        break;
                    }
                }
            }
        }

        if(pos == false) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
