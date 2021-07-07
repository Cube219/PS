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

constexpr int NUM = 50;


int tNum;
long double c, m, p, v;

long double bt(long double cc, long double cm, long double cp, long double curp, int cnt)
{
    if(cc < 0 && cm < 0) return curp * cnt;

    long double res = cp * curp * cnt;

    // c
    if(cc - v > 10e-7) {
        long double gap = cc - v;
        long double nc = cc - v;
        long double nm = cm + v / 2.0;
        long double np = cp + v / 2.0;
        if(nm < 0) {
            np = cp + v;
        }
        double ncurp = curp *  cc;
        res += bt(nc, nm, np, ncurp, cnt + 1);
    } else if(cc >= 0) {
        long double nm = cm + cc / 2.0;
        long double np = cp + cc / 2.0;
        if(nm < 0) np = cp + cc;
        double ncurp = curp *  cc;
        res += bt(-10000, nm, np, ncurp, cnt + 1);
    }

    // m
    if(cm - v > 10e-7) {
        long double gap = cm - v;
        long double nc = cc + v / 2.0;
        long double nm = cm - v;
        long double np = cp + v / 2.0;
        if(nc < 0) {
            np = cp + v;
        }
        double ncurp = curp * cm;
        res += bt(nc, nm, np, ncurp, cnt + 1);
    } else if(cm >= 0) {
        long double nc = cc + cm / 2.0;
        long double np = cp + cm / 2.0;
        if(nc < 0) np = cp + cm;
        double ncurp = curp * cm;
        res += bt(nc, -10000, np, ncurp, cnt + 1);
    }

    return res;
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
        cin >> c >> m >> p >> v;
        cout << fixed << setprecision(8) << bt(c, m, p, 1.0, 1) <<"\n";
    }

    return 0;
}
