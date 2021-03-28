#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr ll MOD = 998244353;

int n, m;
ll fact[300001], factInv[300001];

ll mpow(ll x, ll mm)
{
    if(!mm) return 1;
    ll tmp = mpow(x, mm / 2);
    tmp = tmp * tmp % MOD;
    if(mm % 2) return tmp * x % MOD;
    return tmp;
}

ll Com(ll x, ll r)
{
    return (((fact[x] * factInv[r]) % MOD) * factInv[x - r]) % MOD;
}

void init()
{
    fact[0] = 1;
    for(int i = 1; i <= 300000; i++) fact[i] = fact[i - 1] * i % MOD;
    factInv[300000] = mpow(fact[300000], MOD - 2);
    for(int i = 300000 - 1; i >= 0; i--) factInv[i] = factInv[i + 1] * (i + 1) % MOD;
}

constexpr int MAXN = 300000;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        min_factor[i] = i;
    }

    for(int i = 2; i * i <= MAXN; i++) {
        if(min_factor[i] == i) {
            for(int j = i * i; j <= MAXN; j += i) {
                if(min_factor[j] == j) {
                    min_factor[j] = i;
                }
            }
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


ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    init();
    init_primes();
    res = 0;

    for(int i = 1; i <= m; ++i) {
        get_f_primes(i);
        ll v = 1;
        for(int j = 0; j < fPrimes.size(); ++j) {
            ll num = fPrimes[j].second;
            v = (v * Com(num + n - 1, n - 1)) % MOD;
        }
        res = (res + v) % MOD;
    }
    cout << res;

    return 0;
}
