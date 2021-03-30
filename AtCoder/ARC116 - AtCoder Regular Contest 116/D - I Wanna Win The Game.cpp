#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr ll MOD = 998244353;

ll pw(ll a, ll b)
{
    ll res = 1;
    while(b > 0) {
        if(b % 2 != 0) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b /= 2;
    }
    return res;
}

ll fact[300001], invfact[300001];
void init_fact()
{
    fact[0] = 1;
    for(int i = 1; i <= 300000; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[300000] = pw(fact[300000], MOD - 2);
    for(int i = 300000 - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % MOD;
}

ll comb(int n, int r)
{
    ll factn = fact[n];
    ll invnr = invfact[n - r];
    ll invr = invfact[r];
    return factn % MOD * invnr % MOD * invr % MOD;
}

int n, m;
ll dp[15][5001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    cin >> n >> m;

    for(int bitNum = 0; bitNum <= n; bitNum += 2) {
        dp[0][bitNum] = comb(n, bitNum);
    }

    for(int i = 1; i <= 14; ++i) {
        for(int j = 0; j <= m; ++j) {
            for(int bitNum = 0; bitNum <= n; bitNum += 2) {
                int newj = j - (1 << i) * bitNum;
                if(newj < 0) break;
                dp[i][j] = (dp[i][j] + dp[i - 1][newj] * comb(n, bitNum) % MOD) % MOD;
            }
        }
    }

    cout << dp[14][m];

    return 0;
}
