#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr double PI = 3.141592653;

struct Point
{
    ll x, y;
};
Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}

int n, l;
vector<Point> d;

ll ccw(Point l1, Point l2)
{
    return l1.x * l2.y - l2.x * l1.y;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y;
    }
    sort(d.begin(), d.end(), [](const Point& l, const Point& r) {
        if(l.y == r.y) return l.x > r.x;
        return l.y > r.y;
    });
    Point pivot = d.back();
    d.pop_back();
    sort(d.begin(), d.end(), [pivot](const Point& l, const Point& r) {
        Point l1 = l - pivot;
        Point r1 = r - pivot;
        ll cw = ccw(l1, r1);
        if(cw == 0) {
            if(l.y == r.y) return l.x < r.x;
            return l.y < r.y;
        } else if(cw > 0) {
            return true;
        } else {
            return false;
        }
    });

    vector<Point> st;
    st.push_back(pivot);
    st.push_back(d[0]);
    for(int i = 1; i < d.size(); ++i) {
        if(st.size() <= 1) {
            st.push_back(d[i]);
            continue;
        }
        Point p2 = d[i];
        Point p1 = st[st.size() - 1];
        Point p0 = st[st.size() - 2];

        Point l1 = p1 - p0;
        Point l2 = p2 - p0;
        ll cw = ccw(l1, l2);

        if(cw > 0) {
            st.push_back(d[i]);
        } else {
            st.pop_back();
            i--;
        }
    }
    st.push_back(pivot);
    double res = 0;
    for(int i = 1; i < st.size(); i++){
        ll dx = st[i].x - st[i - 1].x;
        ll dy = st[i].y - st[i - 1].y;
        res += sqrt(dx * dx + dy * dy);
    }
    st.push_back(st[1]);
    for(int i = 2; i < st.size(); ++i) {
        Point l1 = st[i - 2] - st[i - 1];
        Point l2 = st[i] - st[i - 1];
        double len1 = sqrt(l1.x * l1.x + l1.y * l1.y);
        double len2 = sqrt(l2.x * l2.x + l2.y * l2.y);
        ll dot = l1.x * l2.x + l1.y * l2.y;
        double cost = dot / len1;
        cost /= len2;
        double t = acos(cost);
        t = PI - t;
        res += t * l;
    }
    cout << (ll)round(res);

    return 0;
}
