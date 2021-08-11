#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll mod;
// template <int mod>
struct BiCoeff_Lucas
{
    // ll ncr[mod + 1][mod + 1];
    vector<vector<ll>> ncr;

    ll pw(ll a, ll b)
    {
        ll res = 1;
        while(b > 0) {
            if(b & 1) {
                res = res * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    // O(mod^2)
    void init()
    {
        ncr.resize(mod);
        for(int i = 0; i < mod; ++i) {
            ncr[i].resize(mod, 0);
        }

        for(int i = 0; i < mod; ++i) {
            ncr[i][0] = 1;
            ncr[i][i] = 1;
        }
        for(int i = 1; i < mod; ++i) {
            for(int j = 1; j < mod; ++j) {
                ncr[i][j] = ncr[i - 1][j - 1] + ncr[i - 1][j];
                ncr[i][j] %= mod;
            }
        }
    }

    // O(logn + logr), Only use when MOD is prime
    ll get(ll n, ll r)
    {
        ll res = 1;
        while(n > 0 || r > 0) {
            ll a = n % mod;
            ll b = r % mod;
            res *= ncr[a][b];
            res %= mod;

            n /= mod;
            r /= mod;
        }
        return res;
    }
};

ll n, k;
BiCoeff_Lucas bi;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> mod;

    bi.init();
    cout << bi.get(n, k);

    return 0;
}
