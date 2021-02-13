#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

using ll = long long int;

int tNum;
int n;
struct Point
{
    ll x;
    ll y;
};
bool operator<(const Point& l, const Point& r)
{
    if(l.x == r.x) return l.y < r.y;
    return l.x < r.x;
}
Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}
Point g[102];
vector<Point> d;

ll ccw(ll x1, ll y1, ll x2, ll y2)
{
    return x1 * y2 - x2 * y1;
}

double res;

double maxdis(int i1, int i2)
{
    double res = 0;
    Point l1 = d[i2] - d[i1];
    double ldis = sqrt(l1.x * l1.x + l1.y * l1.y);

    for(int i = 0; i < d.size(); ++i) {
        if(i == i1 || i == i2) continue;

        Point l2 = d[i] - d[i1];
        ll area = abs(ccw(l1.x, l1.y, l2.x, l2.y));
        double h = (double)area / ldis;

        if(res < h) res = h;
    }

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt = 0;
    while(1) {
        tt++;

        cin >> n;
        if(n == 0) break;

        for(int i = 0; i < n; ++i) {
            cin >> g[i].x >> g[i].y;
        }
        sort(g, g + n);
        sort(g + 1, g + n, [](const Point& l, const Point& r) {
            Point d1 = l - g[0];
            Point d2 = r - g[0];

            ll res = ccw(d1.x, d1.y, d2.x, d2.y);
            if(res > 0) return true;
            else if(res < 0) return false;
            else {
                if(d1.y != d2.y) return d1.y < d2.y;
                else return d1.x < d2.x;
            }
        });

        d.clear();

        d.push_back(g[0]);
        d.push_back(g[1]);
        for(int i = 2; i < n; ++i) {
            while(d.size() >= 2) {
                int ds = d.size();
                Point p1 = d[ds - 2];
                Point p2 = d[ds - 1];
                Point p3 = g[i];

                Point d1 = p2 - p1;
                Point d2 = p3 - p2;

                ll res = ccw(d1.x, d1.y, d2.x, d2.y);
                if(res < 0) {
                    d.pop_back();
                } else {
                    break;
                }
            }
            d.push_back(g[i]);
        }

        res = 987654321;
        for(int i = 0; i < d.size(); ++i) {
            double tmp;
            if(i == d.size() - 1) {
                tmp = maxdis(i, 0);
            } else {
                tmp = maxdis(i, i + 1);
            }
            if(res > tmp) res = tmp;
        }
        cout.precision(2);
        res += 0.005;
        cout << "Case " << tt << ": " << fixed << res << "\n";
    }

    return 0;
}
