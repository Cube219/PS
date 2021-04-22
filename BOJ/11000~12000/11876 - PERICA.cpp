#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

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

ll fact[100000 + 1], invfact[100000 + 1];

void init_fact()
{
    fact[0] = 1;
    for(int i = 1; i <= 100000; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[100000] = pw(fact[100000], MOD - 2);
    for(int i = 100000 - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % MOD;
}

ll comb(int n, int r)
{
    ll factn = fact[n];
    ll invnr = invfact[n - r];
    ll invr = invfact[r];
    return factn % MOD * invnr % MOD * invr % MOD;
}


int n, k;
int d[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_fact();

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sort(d, d + n);

    ll res = 0;

    for(int i = k - 1; i < n; ++i) {
        ll com = comb(i , k - 1);
        res += (ll)d[i] * com;
        res %= MOD;
    }

    cout << res;

    return 0;
}
