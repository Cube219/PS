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
    int n, m;
    cin >> n >> m;
    struct Nxt { int nxt, idx; bool isRev; };
    vector<vector<Nxt>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back({ v, i, false });
        g[v].push_back({ u, i, true });
    }

    // -1: < / 0: = / 1: >
    vector<int> res(m, -2);

    vector<int> dep(n, -1);
    int dNum;
    vector<pair<int, int>> st;
    auto bcc_dfs = [&](auto&& self, int cur, int preIdx) -> int {
        dep[cur] = dNum++;
        int ret = dep[cur];

        for(auto [nxt, idx, isRev] : g[cur]) {
            if(idx == preIdx) continue;

            if(res[idx] == -2) {
                res[idx] = isRev ? -1 : 1;
            }

            if(dep[nxt] == -1 || dep[nxt] < dep[cur]) st.push_back({ cur, nxt });
            if(dep[nxt] == -1) {
                int t = self(self, nxt, idx);
                if(t >= dep[cur]) {
                    int egNum = 0;
                    while(1) {
                        auto eg = st.back();
                        st.pop_back();
                        egNum++;

                        if(eg.first == cur) break;
                    }
                    if(egNum == 1) {
                        res[idx] = 0;
                    }
                }
                ret = min(ret, t);
            } else ret = min(ret, dep[nxt]);
        }

        return ret;
    };

    for(int i = 0; i < n; ++i) {
        if(dep[i] == -1) {
            dNum = 0;
            bcc_dfs(bcc_dfs, i, -1);
        }
    }

    for(int v : res) {
        if(v == -1) cout << "<\n";
        else if(v == 0) cout << "=\n";
        else cout << ">\n";
    }
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
