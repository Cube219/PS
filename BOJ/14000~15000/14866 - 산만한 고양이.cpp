#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n), down(n), up(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<pair<int, int>>> bcc;
    vector<int> d(n, 0), isCut(n, false);
    vector<pair<int, int>> st;
    int dNum;
    auto dfs = [&](auto&& self, int cur, int pre) -> int {
        d[cur] = ++dNum;

        int ret = d[cur];
        int cNum = 0;
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;

            if(d[nxt] == 0 || d[cur] > d[nxt]) {
                st.push_back({ cur, nxt });
            }

            if(d[nxt] == 0) {
                cNum++;
                int t = self(self, nxt, cur);
                if(t >= d[cur]) {
                    if(d[cur] != 1) isCut[cur] = true;

                    bcc.push_back({});
                    vector<pair<int, int>>& cbcc = bcc.back();
                    while(1) {
                        auto top = st.back();
                        st.pop_back();

                        cbcc.push_back(top);
                        if(top.first == cur) break;
                    }
                }
                ret = min(ret, t);
            } else ret = min(ret, d[nxt]);
        }

        if(d[cur] == 1 && cNum > 1) isCut[cur] = true;

        return ret;
    };
    for(int i = 0; i < n; ++i) {
        if(d[i] == 0) {
            dNum = 0;
            dfs(dfs, i, -1);
        }
    }
    // bridges: bcc[i].size() == 1

    int cycleNum = 0;
    vector<int> cnt(n, 0), deg(n, 0);
    for(auto& b : bcc) {
        if(b.size() == 1) continue;
        cycleNum++;
        int egNum = b.size();
        vector<int> vList;
        for(auto [u, v] : b) {
            if(deg[u] == 0) vList.push_back(u);
            deg[u]++;
            if(deg[v] == 0) vList.push_back(v);
            deg[v]++;
        }
        int vNum = vList.size();
        for(int v : vList) {
            if(deg[v] >= egNum - vNum + 2) cnt[v]++;
        }

        for(auto [u, v] : b) {
            deg[u]--; deg[v]--;
        }
    }

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        if(cnt[i] == cycleNum) res += i + 1;
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
