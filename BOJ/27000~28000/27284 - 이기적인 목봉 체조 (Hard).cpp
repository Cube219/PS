#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> h(n), s(n), hh;
    for(int i = 0; i < n; ++i) {
        cin >> h[i] >> s[i];
        hh.push_back(h[i]);
    }

    sort(hh.begin(), hh.end());
    hh.erase(unique(hh.begin(), hh.end()), hh.end());
    for(auto& v : h) v = lower_bound(hh.begin(), hh.end(), v) - hh.begin();

    vector<ll> dp(n, 0);
    {
        ll curMx = -1;
        ll sSum = 0;
        for(int i = 0; i < n; ++i) {
            if(curMx < h[i]) {
                curMx = h[i];
                sSum = 0;
            }
            if(curMx == h[i]) sSum += s[i];
            dp[i] = sSum;
        }
    }

    for(int i = 1; i < m; ++i) {
        vector<ll> ndp(n, 0);

        // <hIdx, mxDp>
        multimap<ll, ll> mp;
        multiset<ll> mxSet;
        vector<ll> mxList(hh.size(), -LNF);
        auto update = [&](ll hIdx, ll v) {
            auto it = mxSet.find(mxList[hIdx]);
            if(it != mxSet.end()) mxSet.erase(it);

            mxList[hIdx] = v;
            mxSet.insert(v);
        };

        for(int j = i; j < n; ++j) {
            auto it = mp.lower_bound(h[j]);
            ll prevDpMax = 0;
            for(auto it2 = mp.begin(); it2 != it; it2 = mp.erase(it2)) {
                auto [hIdx, mxDp] = *it2;
                update(hIdx, -LNF);
                prevDpMax = max(prevDpMax, mxDp);
            }

            // 기존 값 update
            update(h[j], mxList[h[j]] + s[j]);

            // 새로운 값 update
            prevDpMax = max(prevDpMax, dp[j - 1]);
            if(mxList[h[j]] < prevDpMax + s[j]) update(h[j], prevDpMax + s[j]);
            mp.insert({ h[j], prevDpMax });

            ndp[j] = *prev(mxSet.end());
        }

        dp = move(ndp);
    }

    cout << dp[n - 1];
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
