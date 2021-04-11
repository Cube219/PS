#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

using ll = long long int;

ll r, x, y;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> r >> x >> y;
    x = x * x;
    y = y * y;
    long double tt = sqrtl(x + y);
    long double k = ceill(tt / r);
    ll lk = (ll)(k);

    if(lk == 1) {
        if((x+y) < r*r) {
            lk = 2;
        }
    }

    cout << lk;

    return 0;
}
