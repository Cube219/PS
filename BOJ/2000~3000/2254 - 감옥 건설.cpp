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
    return { l.x - r.x, l.y - r.y };
}

ll ccw(Point v1, Point v2)
{
    return v1.x * v2.y - v2.x * v1.y;
}

int n;
Point p;
vector<Point> d;
bool isIn[1001];
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> p.x >> p.y;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y;
    }

    while(d.size() > 2) {
        sort(d.begin(), d.end(), [](const Point& l, const Point& r) {
            if(l.y == r.y) return l.x > r.x;
            return l.y > r.y;
        });
        Point pivot = d.back();
        d.pop_back();
        sort(d.begin(), d.end(), [pivot](const Point& l, const Point& r) {
            Point l1 = l - pivot;
            Point r1 = r - pivot;
            ll res = ccw(l1, r1);
            if(res == 0) {
                if(l.y == r.y) return l.x < r.x;
                return l.y < r.y;
            } else if(res > 0) return true;
            else return false;
        });

        vector<Point> st;
        vector<int> stIdx;
        st.push_back(pivot);
        st.push_back(d[0]);
        stIdx.push_back(-1);
        stIdx.push_back(0);
        for(int i = 0; i < d.size(); ++i) {
            isIn[i] = false;
        }
        isIn[0] = true;
        for(int i = 1; i < d.size(); ++i) {
            Point p2 = d[i];
            Point p1 = st[st.size()-1];
            Point p0 = st[st.size()-2];

            Point line = p1 - p0;
            Point line2 = p2 - p0;
            ll cw = ccw(line, line2);
            if(cw >= 0) {
                st.push_back(d[i]);
                stIdx.push_back(i);
                isIn[i] = true;
            } else {
                isIn[stIdx.back()] = false;
                st.pop_back();
                stIdx.pop_back();
                i--;
            }
        }
        bool ispos = true;
        Point cur = pivot;
        for(int i = 0; i < d.size(); ++i) {
            if(isIn[i] == false) continue;
            Point nxt = d[i];
            Point line = nxt - cur;
            Point line2 = p - cur;

            ll cw = ccw(line, line2);
            if(cw <= 0) {
                ispos = false;
                break;
            }
            cur = nxt;
        }
        {
            Point nxt = pivot;
            Point line = nxt - cur;
            Point line2 = p - cur;
            ll cw = ccw(line, line2);
            if(cw <= 0) {
                ispos = false;
            }
        }
        if(ispos == false) break;

        res++;
        vector<Point> tmp;
        for(int i = 0; i < d.size(); ++i) {
            if(isIn[i] == false) tmp.push_back(d[i]);
        }
        d.clear();
        d.assign(tmp.begin(), tmp.end());
    }

    cout << res;

    return 0;
}
