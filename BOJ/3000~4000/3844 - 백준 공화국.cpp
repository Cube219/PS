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

constexpr int MAXN = 10000000;
vector<int> min_factor;
vector<int> primes;
vector<pair<int, int>> fPrimes;

void init_primes()
{
    min_factor.resize(MAXN + 1, 0);
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

int n;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes();

    while(1) {
        cin >> n;
        if(n == 0) break;

        ll res = 1;
        for(int p : primes) {
            if(p > n) break;
            ll cnt = 0;
            for(ll i = p; i <= n; i *= p) {
                cnt += (ll)n / i;
            }
            if(cnt == 0) continue;

            if(cnt % 2 == 1) cnt--;
            ll pp = p;
            while(cnt > 0) {
                if(cnt & 1) {
                    res *= pp;
                    res %= MOD;
                }
                cnt = cnt >> 1;
                pp *= pp;
                pp %= MOD;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
