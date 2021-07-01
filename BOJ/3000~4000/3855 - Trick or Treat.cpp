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

int n;
double hx[50001], hy[50001];

double tfunc(double x)
{
    double res = 0;
    for(int i = 0; i < n; ++i) {
        double dx = x - hx[i];
        double dis = sqrt(dx * dx + hy[i] * hy[i]);
        res = max(res, dis);
    }
    return res;
}

pair<double, double> tsearch(double minv, double maxv)
{
    double l = minv, r = maxv;
    while(r - l >= 10e-6) {
        double p = (l * 2.0 + r) / 3.0;
        double q = (l + r * 2.0) / 3.0;

        double pv = tfunc(p);
        double qv = tfunc(q);
        if(pv <= qv) r = q;
        else l = p;
    }

    double res = tfunc((l + r) / 2.0);
    return { (l + r) / 2.0, res };
}


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n;
        if(n == 0) break;
        for(int i = 0; i < n; ++i) {
            cin >> hx[i] >> hy[i];
        }

        auto res = tsearch(-200000, 200000);
        cout << fixed << setprecision(8) << res.first << " " << res.second << "\n";
    }

    return 0;
}
