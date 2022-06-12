#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> s(n - 1);
    for(auto& v : s)cin >> v;
    vector<ll> x(m);
    for(auto& v : x) cin >> v;

    map<ll, int> mp1, mp2;
    mp1.insert({ 0, 1 });
    ll cur = 0;
    for(int i = 1; i < n; ++i) {
        cur = s[i - 1] - cur;
        if(i & 1) {
            auto it = mp2.find(cur);
            if(it == mp2.end()) it = mp2.insert({ cur, 0 }).first;

            it->second++;
        } else {
            auto it = mp1.find(cur);
            if(it == mp1.end()) it = mp1.insert({ cur, 0 }).first;

            it->second++;
        }
    }

    auto ck = [&](ll xx) {
        ll res = 0;

        for(int j = 0; j < m; ++j) {
            auto it2 = mp1.lower_bound(x[j] - xx);
            if(it2 == mp1.end() || it2->first + xx != x[j]) continue;

            res += it2->second;
        }

        for(int j = 0; j < m; ++j) {
            auto it2 = mp2.lower_bound(xx + x[j]);
            if(it2 == mp2.end() || it2->first - xx != x[j]) continue;

            res += it2->second;
        }
        return res;
    };

    ll res = 0;
    for(auto it : mp1) {
        for(int i = 0; i < m; ++i) {
            ll xx = x[i] - it.first;

            res = max(res, ck(xx));
        }
    }
    for(auto it : mp2) {
        for(int i = 0; i < m; ++i) {
            ll xx = it.first - x[i];

            res = max(res, ck(xx));
        }
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
