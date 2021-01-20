#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;

ll n, k;
ll res;

constexpr ll MOD = 1000000007;

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

    cin >> n >> k;

    ll up = 1;
    for(ll i = n; i >= n - k + 1; i--) {
        up = (up * i) % MOD;
    }
    ll down = 1;
    for(int i = 2; i <= k; i++) {
        down = (down * i) % MOD;
    }
    res = divmod(up, down, MOD);

    cout << res;

    return 0;
}
