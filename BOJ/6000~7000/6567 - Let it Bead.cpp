#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

using ll = long long int;

int n, c;

ll pw(ll a, ll b)
{
    ll res = 1;
    while(b > 0) {
        if((b & 1) > 0) {
            res *= a;
        }
        a *= a;
        b >>= 1;
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

    while(1) {
        cin >> c >> n;
        if(c == 0 && n == 0) break;

        ll res = 0;
        for(int i = 0; i < n; ++i) {
            res += pw(c, gcd(n, i));
        }
        if(n % 2 == 1) {
            res += n * pw(c, (n + 1) / 2);
        } else {
            res += n / 2 * pw(c, n / 2);
            res += n / 2 * pw(c, n / 2 + 1);
        }
        res /= n * 2;
        cout << res << "\n";
    }

    return 0;
}
