#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXN = 1000010;
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

// ep[i] = f^a(1 - 1/f)...


int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n, c;
        cin >> n >> c;
        vector<int> d(n);
        vector<int> isprime(n, 1);
        for(auto& v : d) cin >> v;
        for(int i = 0; i < n; ++i) {
            if(min_factor[d[i]] != d[i]) isprime[i] = 0;
        }

        vector<ll> dpl(n, 0), dpr(n, 0);
        for(int i = 0; i < n; ++i) {
            if(d[i] != 1) continue;

            dpl[i] = 1;
            if(i - c >= 0) dpl[i] += dpl[i - c];
        }
        for(int i = n - 1; i >= 0; --i) {
            if(d[i] != 1) continue;

            dpr[i] = 1;
            if(i + c < n) dpr[i] += dpr[i + c];
        }

        ll res = 0;
        for(int i = 0; i < n; ++i) {
            if(isprime[i] == 0) continue;

            ll lcnt = 0;
            if(i - c >= 0) lcnt = dpl[i - c];
            ll rcnt = 0;
            if(i + c < n) rcnt = dpr[i + c];

            res += lcnt;
            res += rcnt;
            res += lcnt * rcnt;
        }
        cout << res << "\n";
    }

    return 0;
}
