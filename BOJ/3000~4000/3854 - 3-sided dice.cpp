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

bool isInLine(Point lp1, Point lp2, Point p)
{
    Point l1 = lp2 - lp1;
    Point l2 = p - lp1;
    ll cw = ccw(l1, l2);
    if(cw != 0) return false;
    else {
        ll minx = lp1.x, maxx = lp2.x;
        ll miny = lp1.y, maxy = lp2.y;
        if(minx > maxx) swap(minx, maxx);
        if(miny > maxy) swap(miny, maxy);
        if((minx < p.x && p.x < maxx) || (miny < p.y && p.y < maxy)) return true;
        else return false;
    }
}

bool isInPolygon(vector<Point>& pol, Point p)
{
    if(pol.size() == 1) return false;
    else if(pol.size() == 2) return isInLine(pol[0], pol[1], p);

    bool isline = true;
    Point a = pol[1] - pol[0];
    Point b = pol[2] - pol[0];
    if(ccw(a, b) != 0) isline = false;
    if(isline == true) {
        for(int i = 1; i < pol.size(); ++i) {
            Point cur = pol[i - 1];
            Point nxt = pol[i];
            if(isInLine(nxt, cur, p) == true) return true;
        }
        return false;
    } else {
        ll last = 0;
        for(int i = 1; i < pol.size(); ++i) {
            Point cur = pol[i - 1];
            Point nxt = pol[i];
            Point l1 = nxt - cur;
            Point l2 = p - cur;
            ll cw = ccw(l1, l2);
            if(cw == 0) {
                return false;
            } else if(last != 0 && last * cw < 0) {
                return false;
            }
            if(cw < 0) last = -1;
            else last = 1;
        }
    }

    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        int a, b, c;
        cin >> a >> b >> c;
        if(a == 0 && b == 0 && c == 0) break;
        vector<Point> tri(4);
        tri[0] = { a, b };

        cin >> a >> b >> c;
        tri[1] = { a, b };
        cin >> a >> b >> c;
        tri[2] = { a, b };
        tri[3] = tri[0];

        cin >> a >> b >> c;

        if(isInPolygon(tri, { a, b }) == true) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
