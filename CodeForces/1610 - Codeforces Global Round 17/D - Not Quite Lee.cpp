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

template <int N, int mod>
struct BiCoeff
{
    ll fact[N + 1], invfact[N + 1];

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

    void init()
    {
        fact[0] = 1;
        for(int i = 1; i <= N; ++i) fact[i] = fact[i - 1] * i % mod;
        invfact[N] = pw(fact[N], mod - 2);
        for(int i = N - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
    }

    ll get(int n, int r)
    {
        ll factn = fact[n];
        ll factrnr = fact[r] * fact[n - r] % mod;
        return factn * pw(factrnr, mod - 2) % mod;
    }
};

int n;
vector<int> a, cnt;
BiCoeff<200001, MOD> bc;
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bc.init();

    cin >> n;
    a.resize(n);
    cnt.resize(32, 0);
    res = 1;

    for(auto& v : a) {
        cin >> v;
        int t = v;
        for(int i = 0; i < 32; ++i) {
            if(t & 1) {
                cnt[i]++;
                break;
            }
            t >>= 1;
        }
        res = (res * 2) % MOD;
    }

    ll other = 1;
    for(int i = 32 - 1; i >= 1; --i) {
        for(int j = 1; j <= cnt[i]; j += 2) {
            ll v = bc.get(cnt[i], j) * other % MOD;
            res = (res - v + MOD) % MOD;
        }
        for(int j = 0; j < cnt[i]; ++j) {
            other = (other * 2) % MOD;
        }
    }

    cout << (res - 1 + MOD) % MOD;

    return 0;
}
