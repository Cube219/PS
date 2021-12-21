#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_map>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<vector<pair<int, int>>> bcc;
    vector<int> d(n, 0), isCut(n, false);
    vector<pair<int, int>> st;
    int dNum;
    auto dfs = [&](auto&& self, int cur, int pre) -> int {
        d[cur] = ++dNum;

        int ret = d[cur];
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;

            if(d[nxt] == 0 || d[cur] > d[nxt]) {
                st.push_back({ cur, nxt });
            }

            if(d[nxt] == 0) {
                int t = self(self, nxt, cur);
                if(t >= d[cur]) {
                    if(d[cur] != 0 || d[nxt] > 1) isCut[cur] = true;

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

        return ret;
    };
    for(int i = 0; i < n; ++i) {
        if(d[i] == 0) {
            dNum = 0;
            dfs(dfs, i, -1);
        }
    }

    vector<int> idx(n);
    vector<vector<int>> g2;
    for(int i = 0; i < n; ++i) {
        if(isCut[i]) {
            g2.emplace_back();
            idx[i] = g2.size() - 1;
        }
    }
    unordered_map<ll, int> bridges;
    vector<char> isUse(n, 0);
    for(auto& b : bcc) {
        g2.emplace_back();
        int cur = g2.size() - 1;
        for(auto& p : b) {
            if(!isUse[p.first]) {
                if(isCut[p.first]) {
                    g2[cur].emplace_back(idx[p.first]);
                    g2[idx[p.first]].emplace_back(cur);
                } else idx[p.first] = cur;
                isUse[p.first] = true;
            }
            if(!isUse[p.second]) {
                if(isCut[p.second]) {
                    g2[cur].emplace_back(idx[p.second]);
                    g2[idx[p.second]].emplace_back(cur);
                } else idx[p.second] = cur;
                isUse[p.second] = true;
            }
        }
        if(b.size() == 1) {
            ll u = b[0].first;
            ll v = b[0].second;
            if(u > v) swap(u, v);
            bridges.insert({ u << 32 | v, cur });
        }
        for(auto& p : b) {
            isUse[p.first] = false;
            isUse[p.second] = false;
        }
    }

    vector<vector<int>> table(g2.size(), vector<int>(18, -1));
    vector<int> dep(g2.size(), 0);
    auto dfs2 = [&](auto&& self, int cur, int pre)->void {
        for(int nxt : g2[cur]) {
            if(nxt == pre) continue;
            table[nxt][0] = cur;
            dep[nxt] = dep[cur] + 1;
            self(self, nxt, cur);
        }
    };
    dfs2(dfs2, idx[0], -1);
    for(int j = 1; j < 18; ++j) {
        for(int i = 0; i < g2.size(); ++i) {
            int tmp = table[i][j - 1];
            if(tmp == -1) continue;
            table[i][j] = table[tmp][j - 1];
        }
    }
    auto lca = [&](int a, int b) {
        if(dep[a] > dep[b]) swap(a, b);
        int gap = dep[b] - dep[a];
        for(int i = 0; gap > 0; ++i, gap >>= 1) {
            if(gap & 1) b = table[b][i];
        }
        for(int i = 18 - 1; i >= 0; --i) {
            if(table[a][i] != table[b][i]) {
                a = table[a][i];
                b = table[b][i];
            }
        }
        if(a != b) a = table[a][0];
        return a;
    };

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int f, a, b;
        cin >> f >> a >> b;
        a = idx[a - 1];
        b = idx[b - 1];
        if(f == 1) {
            int g1, g2;
            cin >> g1 >> g2;
            g1--; g2--;
            if(g1 > g2) swap(g1, g2);
            auto it = bridges.find((ll)g1 << 32 | (ll)g2);
            if(a == b || it == bridges.end()) cout << "yes\n";
            else {
                int c = it->second;
                int l = lca(a, b);
                int l2 = lca(c, l);
                if(l2 != l) cout << "yes\n";
                else if(lca(a, c) == c || lca(b, c) == c) cout << "no\n";
                else cout << "yes\n";
            }
        } else {
            int c;
            cin >> c;
            if(a == b || isCut[c - 1] == false) cout << "yes\n";
            else {
                c = idx[c - 1];
                int l = lca(a, b);
                int l2 = lca(c, l);
                if(l2 != l) cout << "yes\n";
                else if(lca(a, c) == c || lca(b, c) == c) cout << "no\n";
                else cout << "yes\n";
            }
        }
    }
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
