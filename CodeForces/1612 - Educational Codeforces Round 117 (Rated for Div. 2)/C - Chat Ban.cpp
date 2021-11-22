#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
ll k, x;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        ll res = 0;
        cin >> k >> x;

        ll k1 = k * (k + 1) / 2;
        if(k1 < x) {
            res += k;
            x -= k1;

            k--;
            ll a = k * (k + 1) / 2;
            if(a <= x) {
                res += k;
            } else {
                ll lo = -1, hi = k;
                while(lo + 1 < hi) {
                    ll m = (lo + hi) / 2;
                    ll m2 = m * (m + 1) / 2;
                    if(a - m2 >= x) {
                        lo = m;
                    } else {
                        hi = m;
                    }
                }
                res += k - lo;
            }
        } else {
            ll lo = 0, hi = k;
            while(lo + 1 < hi) {
                ll m = (lo + hi) / 2;
                ll m2 = m * (m + 1) / 2;
                if(m2 >= x) {
                    hi = m;
                } else {
                    lo = m;
                }
            }
            res = hi;
        }

        cout << res << "\n";
    }

    return 0;
}
