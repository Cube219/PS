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
    struct Node
    {
        int nxt, cost;
    };
    vector<vector<Node>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
    }

    int res = INF;
    vector<int> order;
    vector<bool> visit(n, false);
    vector<int> curOrder;
    auto bt = [&](auto&& self, int cur, int cnt, int mxCost) -> void {
        visit[cur] = true;
        curOrder.push_back(cur);

        if(cnt == n - 1) {
            bool f = false;
            for(auto [nxt, cost] : g[cur]) {
                if(nxt == 0) {
                    f = true;
                    mxCost = max(mxCost, cost);
                }
            }
            if(f && mxCost < res) {
                res = mxCost;
                order = curOrder;
            }
        } else {
            for(auto [nxt, cost] : g[cur]) {
                if(visit[nxt]) continue;
                self(self, nxt, cnt + 1, max(mxCost, cost));
            }
        }

        curOrder.pop_back();
        visit[cur] = false;
    };
    bt(bt, 0, 0, -1);

    if(res == INF) cout << "-1";
    else {
        cout << res << "\n";
        for(int v : order) cout << v + 1 << " ";
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
