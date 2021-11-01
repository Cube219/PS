#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <numeric>
using namespace std;

using ll = long long int;

int tNum;
ll x, y;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> x >> y;
        ll res;
        if(x < y) {
            ll p = (y / x) * x;
            if(p == y) p -= x;
            res = (y + p) / 2 % y;
        } else if(x == y) {
            res = x;
        } else {
            res = x + y;
        }
        cout << res << "\n";
        assert((res % x) == (y % res));
    }

    return 0;
}
