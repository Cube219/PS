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
constexpr double PI = 3.141592653;

struct Point
{
    double x, y;
};

Point operator+(const Point& l, const Point& r)
{
    return { l.x + r.x, l.y + r.y };
}

Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}

double ccw(Point l1, Point l2)
{
    return l1.x * l2.y - l2.x * l1.y;
}

bool isInLine(Point lp1, Point lp2, Point p)
{
    Point l1 = lp2 - lp1;
    Point l2 = p - lp1;
    double cw = ccw(l1, l2);
    if(cw != 0) return false;
    else {
        double dt, dt2;
        if(lp1.x == lp2.x) {
            dt = fabs(lp1.y - lp2.y);
            dt2 = max(abs(p.y - lp1.y), abs(p.y - lp2.y));
        } else {
            dt = fabs(lp1.x - lp2.x);
            dt2 = max(abs(p.x - lp1.x), abs(p.x - lp2.x));
        }
        if(dt < dt2) return false;
        else return true;
    }
}

bool isInPolygon(vector<Point>& pol, Point p)
{
    if(pol.size() == 1) return false;
    else if(pol.size() == 2) return isInLine(pol[0], pol[1], p);

    for(int i = 1; i < pol.size(); ++i) {
        Point cur = pol[i - 1];
        Point nxt = pol[i];
        Point l1 = nxt - cur;
        Point l2 = p - cur;
        double cw = ccw(l1, l2);
        if(cw == 0) {
            if(isInLine(nxt, cur, p) == true) return true;
            else return false;
        } else if(cw < 0) {
            return false;
        }
    }

    return true;
}

int n;
Point d[1001];
double res;
int res2;

double process(int k)
{
    vector<Point> pol;
    double l = 0;
    double r = 10000000;
    while(fabs(r-l) > 1e-7) {
        double m = (l + r) / 2.0;
        pol.clear();
        double angle = 0.0;
        for(int i = 0; i <= k; ++i) {
            pol.push_back({ m * cos(angle), m * sin(angle) });
            angle += PI * 2.0 / (double)k;
        }
        bool pos = true;
        for(int i = 0; i < n; ++i) {
            if(isInPolygon(pol, d[i]) == true) {
                pos = false;
                break;
            }
        }
        if(pos == true) {
            l = m;
        } else {
            r = m;
        }
    }
    double inlen = l;
    l = 0;
    r = 10000000;
    while(fabs(r - l) > 1e-7) {
        double m = (l + r) / 2.0;
        pol.clear();
        double angle = 0.0;
        for(int i = 0; i <= k; ++i) {
            pol.push_back({ m * cos(angle), m * sin(angle) });
            angle += PI * 2.0 / (double)k;
        }
        bool pos = true;
        for(int i = 0; i < n; ++i) {
            if(isInPolygon(pol, d[i]) == false) {
                pos = false;
                break;
            }
        }
        if(pos == true) {
            r = m;
        } else {
            l = m;
        }
    }
    double outlen = l;

    return (inlen * inlen) / (outlen * outlen);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y;
    }

    for(int i = 3; i <= 8; ++i) {
        double r = process(i);
        if(res < r) {
            res = r;
            res2 = i;
        }
    }

    cout << res2 << " ";
    cout << fixed << setprecision(10) << res;

    return 0;
}
