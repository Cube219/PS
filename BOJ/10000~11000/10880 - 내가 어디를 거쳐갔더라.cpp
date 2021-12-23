#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
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
    // bridges: bcc[i].size() == 1

    vector<int> idx(n);
    vector<vector<int>> g2;
    vector<int> sz;
    for(int i = 0; i < n; ++i) {
        if(isCut[i]) {
            g2.emplace_back();
            sz.push_back(1);
            idx[i] = g2.size() - 1;
        }
    }
    unordered_map<ll, int> bridges;
    vector<char> isUse(n, 0);
    for(auto& b : bcc) {
        g2.emplace_back();
        sz.push_back(0);
        int cur = g2.size() - 1;
        for(auto& p : b) {
            if(!isUse[p.first]) {
                if(isCut[p.first]) {
                    g2[cur].emplace_back(idx[p.first]);
                    g2[idx[p.first]].emplace_back(cur);
                } else {
                    idx[p.first] = cur;
                    sz[cur]++;
                }
                isUse[p.first] = true;
            }
            if(!isUse[p.second]) {
                if(isCut[p.second]) {
                    g2[cur].emplace_back(idx[p.second]);
                    g2[idx[p.second]].emplace_back(cur);
                } else {
                    idx[p.second] = cur;
                    sz[cur]++;
                }
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

    vector<int> tsize(g2.size()), dep(g2.size(), 0);
    vector<vector<int>> table(g2.size(), vector<int>(19, -1));
    auto dfs2 = [&](auto&& self, int cur, int pre) -> int {
        tsize[cur] = sz[cur];
        for(int nxt : g2[cur]) {
            if(nxt == pre) continue;
            table[nxt][0] = cur;
            dep[nxt] = dep[cur] + 1;
            tsize[cur] += self(self, nxt, cur);
        }
        return tsize[cur];
    };
    dfs2(dfs2, 0, -1);

    for(int j = 1; j < 19; ++j) {
        for(int i = 0; i < g2.size(); ++i) {
            int tmp = table[i][j - 1];
            if(tmp == -1) continue;
            table[i][j] = table[tmp][j - 1];
        }
    }

    auto isInLine = [&](int up, int down) {
        if(dep[up] >= dep[down]) return -1;
        int gap = dep[down] - dep[up];
        gap--;
        for(int i = 0; gap > 0; ++i, gap >>= 1) {
            if(gap & 1) down = table[down][i];
        }
        if(table[down][0] != up) return -1;
        else return down;
    };

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        if(isCut[a] == false && isCut[b] == false) {
            cout << n << "\n";
            continue;
        } else if(isCut[a] == false || isCut[b] == false) {
            if(isCut[b] == true) swap(a, b);
            a = idx[a];
            b = idx[b];
            // a가 단절점
            // a subtree안에 b가 있다면 child[a] + 1
            // 아니면 n - sz[a] + 1
            int res = isInLine(a, b);
            if(res != -1) {
                cout << tsize[res] + 1 << "\n";
            } else {
                cout << n - tsize[a] + 1 << "\n";
            }
        } else {
            // 만약 1자로 있다면 child[a] - sz[b] + 2
            // 아니라면 n - sz[a] - sz[b] + 2
            a = idx[a];
            b = idx[b];
            if(dep[a] > dep[b]) swap(a, b);

            int res = isInLine(a, b);
            if(res != -1) {
                cout << tsize[res] - tsize[b] + 2 << "\n";
            } else {
                cout << n - tsize[a] - tsize[b] + 2 << "\n";
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
