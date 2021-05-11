#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll t, n;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t >> n;
    ll l = 1, r = 101000000000;
    while(l + 1 < r) {
        ll m = (l + r) / 2;
        ll newm = m * (100 + t) / 100;
        if(newm - m < n) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l * (100 + t) / 100 + 1;

    return 0;
}
