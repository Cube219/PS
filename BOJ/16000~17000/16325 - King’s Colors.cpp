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

ll fact[3000 + 1], invfact[3000 + 1];

void init_fact()
{
    fact[0] = 1;
    for(int i = 1; i <= 3000; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[3000] = pw(fact[3000], MOD - 2);
    for(int i = 3000 - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % MOD;
}

ll comb(int n, int r)
{
    ll factn = fact[n];
    ll invnr = invfact[n - r];
    ll invr = invfact[r];
    return factn % MOD * invnr % MOD * invr % MOD;
}

int n, k;
vector<int> g[2501];

ll get(int cur, int par, int k)
{
    ll res = 1;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        ll t = get(nxt, cur, k);
        res *= (t * (k - 1)) % MOD;
        res %= MOD;
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

    init_fact();

    cin >> n >> k;
    for(int i = 1; i < n; ++i) {
        int a;
        cin >> a;
        g[a].push_back(i);
        g[i].push_back(a);
    }

    ll res = 0;
    bool f = true;
    for(int i = k; i >= 1; --i) {
        ll t = get(0, -1, i);
        t *= i;
        t %= MOD;
        if(f == true) {
            res += t * comb(k, i);
            res %= MOD;
        } else {
            res = res - (t * comb(k, i) % MOD) + MOD;
            res %= MOD;
        }
        f = !f;
    }

    cout << res;

    return 0;
}
