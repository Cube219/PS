#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000000 + 7;

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

ll fact[200001 + 1], invfact[200001 + 1];

void init_fact()
{
    fact[0] = 1;
    for(int i = 1; i <= 200001; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[200001] = pw(fact[200001], MOD - 2);
    for(int i = 200001 - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % MOD;
}

ll comb(ll n, ll r)
{
    if(n < r || n < 0 || r < 0) return 0;
    ll factn = fact[n];
    ll invnr = invfact[n - r];
    ll invr = invfact[r];
    return factn % MOD * invnr % MOD * invr % MOD;
}

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        ll n, l, r;
        cin >> n >> l >> r;

        ll res = 0;
        ll all = min(r - n, -l + 1);
        if(n % 2 == 0) {
            res += all * comb(n, n / 2);
        } else {
            res += all * (comb(n, n / 2) + comb(n, n / 2 + 1));
        }
        res %= MOD;

        ll k = all;
        for(int i = 0; i < n; ++i) {
            k++;
            ll left = max(0LL, k - (1 - l));
            ll right = max(0LL, k - (r - n));
            ll cnt = min(left, right);
            if(n % 2 == 0) {
                res += comb(n - left - right, n / 2 - cnt);
            } else {
                res += comb(n - left - right, n / 2 - cnt) + comb(n - left - right, n / 2 + 1 - cnt);
            }
            res %= MOD;
        }

        cout << res << "\n";
    }

    return 0;
}
