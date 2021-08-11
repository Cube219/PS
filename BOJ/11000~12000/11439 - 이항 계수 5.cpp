#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXN = 4000000;
int min_factor[MAXN + 1];
vector<int> primes;
vector<pair<int, int>> fPrimes;
int pidx[MAXN + 1];

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
    for(int i = 0; i < primes.size(); ++i) {
        pidx[primes[i]] = i;
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

int tNum;
int n, k, m;

ll pw(ll a, ll b)
{
    ll res = 1;
    while(b > 0) {
        if(b & 1) {
            res *= a;
            res %= m;
        }
        a *= a;
        a %= m;
        b >>= 1;
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

    init_primes();

    cin >> n >> k >> m;
    vector<int> pcnt(primes.size(), 0);
    for(int i = n; i >= n - k + 1; --i) {
        get_f_primes(i);
        for(auto fp : fPrimes) {
            pcnt[pidx[fp.first]] += fp.second;
        }
    }
    for(int i = k; i >= 2; --i) {
        get_f_primes(i);
        for(auto fp : fPrimes) {
            pcnt[pidx[fp.first]] -= fp.second;
        }
    }
    ll res = 1;
    for(int i = 0; i < pcnt.size(); ++i) {
        if(pcnt[i] == 0) continue;
        res *= pw(primes[i], pcnt[i]);
        res %= m;
    }

    cout << res;

    return 0;
}
