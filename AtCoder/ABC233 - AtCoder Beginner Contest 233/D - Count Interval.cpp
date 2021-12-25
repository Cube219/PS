#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    ll res = 0;
    map<ll, int> mp;
    ll cur = 0;
    for(int i = 0; i < n; ++i) {
        cur += d[i];
        auto it = mp.find(cur);
        if(it == mp.end()) it = mp.insert({ cur, 0 }).first;
        it->second++;
    }

    cur = 0;
    for(int i = 0; i < n; ++i) {
        auto it = mp.find(k);
        if(it != mp.end()) {
            res += it->second;
        }

        k += d[i];

        cur += d[i];
        it = mp.find(cur);
        it->second--;
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
