#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
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
    vector<vector<pair<int, int>>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }

    vector<vector<pair<int, int>>> bcc;
    vector<int> d(n, 0), isCut(n, false);
    vector<pair<int, int>> st, bridges, notBridges;
    int dNum;
    auto dfs = [&](auto&& self, int cur, int preEidx) -> int {
        d[cur] = ++dNum;

        int ret = d[cur];
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            int eidx = nx.second;
            if(eidx == preEidx) continue;

            if(d[nxt] == 0 || d[cur] > d[nxt]) {
                st.push_back({ cur, nxt });
            }

            if(d[nxt] == 0) {
                int t = self(self, nxt, eidx);
                if(t > d[cur]) bridges.emplace_back(cur, nxt);
                else notBridges.emplace_back(cur, nxt);

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
        
    vector<int> par(n); iota(par.begin(), par.end(), 0);
    auto find = [&](int a) {
        vector<int> st;
        while(par[a] != a) {
            st.push_back(a);
            a = par[a];
        }
        for(int v : st) par[v] = a;
        return a;
    };
    auto uni = [&](int a, int b) {
        int ar = find(a);
        int br = find(b);
        if(ar == br) return;
        par[br] = ar;
    };
    for(auto& nbr : notBridges) {
        uni(nbr.first, nbr.second);
    }
    vector<vector<int>> g2(n);
    for(auto& br : bridges) {
        int a = find(br.first);
        int b = find(br.second);
        assert(a != b);

        g2[a].push_back(b);
        g2[b].push_back(a);
    }

    vector<int> leaf;
    auto dfs2 = [&](auto&& self, int cur, int p) -> void {
        if(g2[cur].size() == 1) leaf.push_back(cur + 1);
        for(int nxt : g2[cur]) {
            if(nxt == p) continue;
            self(self, nxt, cur);
        }
    };
    dfs2(dfs2, find(0), -1);

    int lnum = leaf.size();
    cout << (lnum + 1) / 2 << "\n";
    for(int i = 0; i < lnum / 2; ++i) {
        cout << leaf[i] << " " << leaf[i + lnum / 2] << "\n";
    }
    if(lnum % 2 == 1) {
        cout << leaf[0] << " " << leaf.back() << "\n";
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
