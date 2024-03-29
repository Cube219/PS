#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll a[3];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 3; ++i) {
        cin >> a[i];
    }
    sort(a, a + 3);
    ll m1 = a[0];
    ll m2 = a[1];
    ll res = 0;

    for(ll z = 3; z <= 10000000; ++z) {
        if(m1 >= z) {
            res += (z - 1) / 2 * 48;
        } else if(m2 >= z) {
            ll ymin = z / 2 + 1;
            ll ymax = min(z - 1, m1);
            if(ymax - ymin + 1 <= 0) break;
            res += (ymax - ymin + 1) * 16;
        } else {
            break;
        }
    }

    cout << res;

    return 0;
}
