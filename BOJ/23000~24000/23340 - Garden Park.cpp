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
    int n;
    cin >> n;
    struct Node
    {
        int nxt, cost;
    };
    vector<vector<Node>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        g[u].push_back({ v, c });
        g[v].push_back({ u, c });
    }

    struct Ret
    {
        ll upNum, downNum;
    };
    struct Data
    {
        int cost;
        ll num;
    };
    ll total = 0;
    auto dfs = [&](auto&& self, int cur, int pre, int preCost) -> Ret {
        vector<Data> up, down;
        for(auto [nxt, cost] : g[cur]) {
            if(nxt == pre) continue;

            Ret ret = self(self, nxt, cur, cost);
            up.push_back({ cost, ret.upNum });
            down.push_back({ cost, ret.downNum });
        }

        sort(up.begin(), up.end(), [](const auto& l, const auto& r) {
            return l.cost < r.cost;
        });
        sort(down.begin(), down.end(), [](const auto& l, const auto& r) {
            return l.cost < r.cost;
        });

        Ret ret = { 1, 1 };

        for(int i = 0; i < up.size(); ++i) {
            if(up[i].cost >= preCost) break;
            ret.upNum += up[i].num;
        }
        for(int i = down.size() - 1; i >= 0; --i) {
            if(down[i].cost <= preCost) break;
            ret.downNum += down[i].num;
        }

        // Calculate total
        for(auto [cost, num] : up) total += num;
        for(auto [cost, num] : down) total += num;

        ll curDown = 0;
        while(up.size() > 0) {
            while(down.size() > 0 && up.back().cost < down.back().cost) {
                curDown += down.back().num;
                down.pop_back();
            }
            total += up.back().num * curDown;
            up.pop_back();
        }

        return ret;
    };
    dfs(dfs, 0, -1, -1);

    cout << total;
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
