#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

using ll = long long int;
constexpr double INF = 999999999999999;

int n;
int x[51], y[51], dx[51], dy[51];

double tfunc(double t)
{
    double minx = INF, maxx = -INF, miny = INF, maxy = -INF;
    for(int i = 0; i < n; ++i) {
        double cx = x[i] + dx[i] * t;
        double cy = y[i] + dy[i] * t;
        minx = min(minx, cx);
        maxx = max(maxx, cx);
        miny = min(miny, cy);
        maxy = max(maxy, cy);
    }

    return max(maxx - minx, maxy - miny);
}

double tsearch()
{
    double l = 0, r = 1000000;
    for(int i = 0; i < 2000; i++) {
        double p = (l * 2 + r) / 3.0;
        double q = (l + r * 2) / 3.0;

        double pv = tfunc(p);
        double qv = tfunc(q);
        if(pv <= qv) r = q;
        else l = p;
    }

    return tfunc(l);
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
        cin >> x[i] >> y[i] >> dx[i] >> dy[i];
    }

    cout << fixed << setprecision(13) << tsearch();

    return 0;
}
