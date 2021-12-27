#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
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
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dep(n, 0), par(n, -1);
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;
            dep[nxt] = dep[cur] + 1;
            par[nxt] = cur;
            self(self, nxt, cur);
        }
    };
    dfs(dfs, 0, -1);
    vector<pair<int, int>> d(n);
    for(int i = 0; i < n; ++i) {
        d[i] = { dep[i], i };
    }
    sort(d.begin(), d.end());

    vector<char> visit(n, false);
    vector<int> c(n, 0);
    for(int i = n - 1; i >= 0; --i) {
        int cur = d[i].second;
        int idx = cur;
        while(cur != -1 && visit[cur] == false) {
            c[idx]++;
            visit[cur] = true;
            cur = par[cur];
        }
    }
    for(int i = 0; i < n; ++i) {
        d[i] = { c[i], i };
    }
    sort(d.begin(), d.end());

    ll r = 0, w = n;
    ll canb = n;
    for(int i = 0; i < k; ++i) {
        if(canb <= 0) break;
        canb -= d.back().first;
        d.pop_back();
        r++;
    }
    ll b = 0;
    if(canb <= 0) {
        r = max(r, (ll)min(n / 2, k));
    } else {
        if(canb <= k) b = canb;
        else {
            ll remain = n - k * 2;
            b = min(canb - k, remain / 2);
            b += k;
        }
    }
    w = n - r - b;

    cout << w * (r - b) << "\n";
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
