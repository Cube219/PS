#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
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

    vector<int> dep(n, 0), sz(n, 0), par(n);
    auto dfs = [&](auto&& self, int cur, int p) -> int {
        sz[cur] = 1;
        for(int nxt : g[cur]) {
            if(nxt == p) continue;
            dep[nxt] = dep[cur] + 1;
            par[nxt] = cur;
            sz[cur] += self(self, nxt, cur);
        }
        return sz[cur];
    };
    par[0] = -1;
    dfs(dfs, 0, -1);

    vector<pair<int, int>> d(n);
    for(int i = 0; i < n; ++i) {
        d[i] = { i, dep[i] };
    }
    sort(d.begin(), d.end(), [](const pair<int, int>& l, const pair<int, int>& r) {
        return l.second > r.second;
    });

    int res = n;
    vector<int> clist;
    auto cut = [&]() {
        sort(clist.begin(), clist.end(), [&](const int& l, const int& r) {
            return sz[l] > sz[r];
        });
        while(clist.size() > k) {
            int c = clist.back();
            int cur = c;
            while(par[cur] != -1) {
                sz[par[cur]] -= sz[c];
                cur = par[cur];
            }
            res -= sz[c];
            clist.pop_back();
        }
        clist.clear();
    };
    int curdep = d[0].second;
    for(int i = 0; i < n; ++i) {
        if(curdep != d[i].second) {
            cut();
            curdep = d[i].second;
        }
        clist.push_back(d[i].first);
    }
    cut();

    cout << res;
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
