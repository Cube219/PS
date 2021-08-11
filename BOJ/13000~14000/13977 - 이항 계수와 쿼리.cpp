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

ll fact[4000000 + 1], invfact[4000000 + 1];

void init_fact()
{
    fact[0] = 1;
    for(int i = 1; i <= 4000000; ++i) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact[4000000] = pw(fact[4000000], MOD - 2);
    for(int i = 4000000 - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % MOD;
}

ll comb(int n, int r)
{
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
        int n, k;
        cin >> n >> k;
        cout << comb(n, k) << "\n";
    }

    return 0;
}
