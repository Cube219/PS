#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll m;

ll pw(ll a, ll b)
{
    ll res = 1;
    while(b > 0) {
        if(b % 2 != 0) {
            res = res * a % m;
        }
        a = a * a % m;
        b /= 2;
    }
    return res;
}

ll fact[10000 + 1], invfact[10000 + 1];

void init_fact()
{
    fact[0] = 1;
    for(int i = 1; i <= 10000; ++i) fact[i] = (ll)fact[i - 1] * i % m;
    invfact[10000] = pw(fact[10000], m - 2);
    for(int i = 10000 - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % m;
}

ll comb(int n, int r)
{
    ll factn = fact[n];
    ll invnr = invfact[n - r];
    ll invr = invfact[r];
    return factn % m * invnr % m * invr % m;
}


int n;
ll dp[405][405];
ll p2[405];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    init_fact();
    p2[0] = 1;
    for(int i = 1; i <= n; ++i) {
        p2[i] = p2[i - 1] * 2;
        p2[i] %= m;
    }

    for(int i = 1; i <= n; ++i) {
        dp[i][i] = p2[i - 1];
    }

    for(int i = 3; i <= n; ++i) {
        for(int j = i; j >= 3; --j) {
            int rightLen = i - j + 1;
            int leftLen = i - rightLen - 1;
            for(int k = 0; k <= leftLen; ++k) {
                ll tmp = dp[leftLen][k] * p2[rightLen - 1] % m;
                tmp *= comb(k + rightLen, rightLen);
                tmp %= m;
                dp[i][rightLen + k] += tmp;
                dp[i][rightLen + k] %= m;
            }
        }
    }
    ll res = 0;
    for(int i = 0; i <= n; ++i) {
        res += dp[n][i];
        res %= m;
    }

    cout << res;

    return 0;
}
