#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
ll dp[200002];
ll sum[200002];
ll x;

constexpr ll MOD = 998244353;

ll divmod(ll a, ll b, ll mod)
{
    ll res = 1;
    ll ex = mod - 2;
    while(ex > 0) {
        if(ex % 2 != 0) {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        ex /= 2;
    }
    res = (res * a) % mod;
    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        x = 1;
        cin >> n;
        for(int i = 1; i <= n; i++) {
            dp[i] = 0;
            sum[i] = 0;

            x = (x * 2) % MOD;
        }

        sum[1] = 1;
        sum[2] = 1;
        dp[1] = 1;
        dp[2] = 1;
        for(int i = 3; i <= n; i++) {
            dp[i] = sum[i - 1];
            sum[i] = (sum[i - 2] + dp[i]) % MOD;
        }
        cout << divmod(sum[n], x, MOD) << "\n";

    return 0;
}
