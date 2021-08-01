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

int a, d, k;
double res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> d >> k;
    int a2 = a;

    double win = (double)d / 100;
    double prob = 1;
    double inc = (double)k / 100 + 1;
    while(win < 1.0) {
        res += (double)a * prob * win;
        prob *= (1.0 - win);
        win *= inc;
        a += a2;
    }
    res += (double)a * prob;

    cout << fixed << setprecision(7) << res;

    return 0;
}
