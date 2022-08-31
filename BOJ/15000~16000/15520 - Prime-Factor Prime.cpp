#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<int> minFactor, primes;

void initSieve(int n)
{
    minFactor.resize(n + 1, 0);
    for(int i = 2; i <= n; i++) {
        if(minFactor[i] == 0) {
            minFactor[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > n) break;
            minFactor[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

void solve()
{
    initSieve(31622);
    ll l, r;
    cin >> l >> r;
    if(l == 1) l = 2;

    vector<int> cnt(r - l + 1, 0);
    vector<ll> remain(r - l + 1);
    iota(remain.begin(), remain.end(), l);
    for(int p : primes) {
        for(ll cur = (l / p) * p; cur <= r; cur += p) {
            if(cur < l) continue;

            int i = cur - l;
            while(remain[i] % p == 0) {
                cnt[i]++;
                remain[i] /= p;
            }
        }
    }

    int res = 0;
    for(int i = 0; i < r - l + 1; ++i) {
        if(remain[i] > 1) cnt[i]++;
        if(minFactor[cnt[i]] == cnt[i]) res++;
    }
    cout << res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
