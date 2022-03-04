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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    map<pair<int, int>, int> egIdx;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);

        egIdx.insert({ { a, b }, i + 1 });
    }

    if((m & 1) == 0) {
        cout << "0\n";
        return;
    }

    vector<vector<pair<int, int>>> bcc;
    vector<int> d(n, 0), isCut(n, false);
    vector<pair<int, int>> st;
    vector<int> sz(n, 0);
    vector<vector<int>> g2(n);
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
                sz[cur]++;
                g2[cur].push_back(nxt);
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
            } else {
                ret = min(ret, d[nxt]);
                if(d[cur] > d[nxt]) sz[nxt]++;
            }
        }

        return ret;
    };
    dNum = 0;
    dfs(dfs, 0, -1);

    // bridges: bcc[i].size() == 1

    auto dfs2 = [&](auto&& self, int cur) -> int {
        for(int nxt : g2[cur]) {
            sz[cur] += self(self, nxt);
        }
        return sz[cur];
    };
    dfs2(dfs2, 0);

    vector<int> res;
    for(auto& b : bcc) {
        if(b.size() != 1) {
            for(auto [u, v] : b) {
                if(u > v) swap(u, v);
                res.push_back(egIdx[{ u, v }]);
            }
        } else {
            auto [u, v] = b[0];
            if(u > v) swap(u, v);

            int num = min(sz[u], sz[v]);
            if(num % 2 == 0) {
                res.push_back(egIdx[{ u, v }]);
            }
        }
    }

    sort(res.begin(), res.end());
    cout << res.size() << "\n";
    for(int v : res) cout << v << " ";
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
