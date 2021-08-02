#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

using ll = long long int;
constexpr int MAXN = 1000000;
constexpr ll MOD = 1000000007;

int n, k;
int ep[MAXN + 1];
ll kpow[MAXN + 1], res;

int min_factor[MAXN + 1];
vector<int> primes;
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        if(min_factor[i] == 0) {
            min_factor[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > MAXN) break;
            min_factor[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

void get_f_primes(int v)
{
    fPrimes.clear();

    while(v > 1) {
        int f = min_factor[v];
        if(fPrimes.size() == 0 || fPrimes.back().first != f) {
            fPrimes.push_back(make_pair(f, 0));
        }
        fPrimes.back().second++;
        v /= f;
    }
}

// (a / b) % mod == (a * b^(mod-2)) % mod
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

void init()
{
    init_primes();

    for(int i = 1; i <= MAXN; ++i) {
        get_f_primes(i);
        ep[i] = 1;
        for(auto& fp : fPrimes) {
            int tmp = 1;
            for(int j = 0; j < fp.second; ++j) {
                tmp *= fp.first;
            }
            ep[i] *= tmp - (tmp / fp.first);
        }
    }

    kpow[0] = 1;
    for(int i = 1; i <= MAXN; ++i) {
        kpow[i] = kpow[i - 1] * k;
        kpow[i] %= MOD;
    }
}


ll pw(ll a, ll b)
{
    ll res = 1;
    while(b > 0) {
        if((b & 1) > 0) {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}

void bt(int idx, int v, int curi)
{
    if(idx == fPrimes.size()) {
        res += kpow[v] * ep[curi / v];
        res %= MOD;
        
        return;
    }

    int cur = v;
    bt(idx + 1, cur, curi);
    for(int i = 0; i < fPrimes[idx].second; ++i) {
        cur *= fPrimes[idx].first;
        bt(idx + 1, cur, curi);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    init();
    ll rr = 0;
    for(int i = 1; i <= n; ++i) {
        res = 0;
        get_f_primes(i);

        bt(0, 1, i);

        if(i % 2 == 1) {
            res += i * kpow[(i + 1) / 2];
        } else {
            res += (i / 2) * kpow[i / 2];
            res %= MOD;
            res += (i / 2) * kpow[i / 2 + 1];
        }
        res %= MOD;
        res = divmod(res, i * 2, MOD);

        rr += res;
        rr %= MOD;
    }

    cout << (rr + 1) % MOD;

    return 0;
}
