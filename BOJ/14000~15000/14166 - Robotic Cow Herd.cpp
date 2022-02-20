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

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> d;
    ll mx = 0;
    ll base = 0;
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        vector<int> tmp(num);
        for(auto& v : tmp) cin >> v;
        sort(tmp.begin(), tmp.end());

        base += tmp[0];
        if(num > 1) {
            d.emplace_back();
            for(int j = 1; j < num; ++j) {
                d.back().push_back(tmp[j] - tmp[0]);
            }
            mx += d.back().back();
        }
    }
    n = d.size();

    sort(d.begin(), d.end());
    vector<ll> d0(n);
    for(int i = 0; i < n; ++i) {
        d0[i] = d[i][0];
    }

    int cnt = 0;
    ll curSum = 0;
    auto bt = [&](auto&& self, int idx, ll limit) -> void {
        if(idx >= 0 && limit < d[idx][0]) {
            idx = upper_bound(d0.begin(), d0.begin() + idx, limit) - d0.begin() - 1;
        }
        if(idx < 0) {
            cnt++;
            curSum += limit + 1;
            return;
        }

        self(self, idx - 1, limit);
        if(cnt >= k) return;
        for(int i = 0; i < d[idx].size() && limit - d[idx][i] >= 0; ++i) {
            self(self, idx - 1, limit - d[idx][i]);
            if(cnt >= k) return;
        }
    };

    ll lo = -1, hi = mx;
    while(lo + 1 < hi) {
        ll md = (lo + hi) / 2;
        cnt = 0;
        curSum = 0;
        bt(bt, n - 1, md);
        // cout << cnt << "\n";
        if(cnt < k) {
            lo = md;
        } else {
            hi = md;
        }
    }
    cnt = 0;
    curSum = 0;
    bt(bt, n - 1, hi - 1);
    cout << (base + hi) * k - curSum;
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
