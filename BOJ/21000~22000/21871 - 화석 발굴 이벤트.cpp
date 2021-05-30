#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll n, k;

int d[101][101];

void pr()
{
    for(int i = -n; i <= n; ++i) {
        for(int j = -n; j <= n; ++j) {
            int v1 = max(abs(i), abs(j));
            int v2 = max(abs(i), abs(j - (int)k));
            if(v1 == v2) d[i + n][j + n] = 1;
            else d[i + n][j + n] = 0;
        }
    }

    for(int i = n; i >= -n; --i) {
        for(int j = -n; j <= n; ++j) {
            cout << d[j + n][i + n] << " ";
        }
        cout << "\n";
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    ll res = 0;
    if(n * 2 < k) res = 0;
    else if(k % 2 == 1) {
        ll num = n - k / 2;
        res = num * (num + 1) / 2;
        res *= 4;
    } else {
        ll num = n - k / 2;
        res = num * (num + 1) / 2;
        res *= 4;
        res += n * 2 + 1;
    }

    cout << (n * 2 + 1) * (n * 2 + 1) - res;

    // while(1) {
    //     cout << "n: " << n << " / " << "k: " << k << "\n";
    //     pr();
    // }



    return 0;
}
