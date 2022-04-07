#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <map>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<vector<int>> par(n, vector<int>(18, -1));
    vector<int> dep(n), cost(n);
    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        for(auto [nxt, c] : g[cur]) {
            if(nxt == pre) continue;
            par[nxt][0] = cur;
            cost[nxt] = cost[cur] + c;
            dep[nxt] = dep[cur] + 1;
            self(self, nxt, cur);
        }
    };
    cost[0] = 0;
    dep[0] = 0;
    dfs(dfs, 0, -1);

    for(int j = 1; j < 18; ++j) {
        for(int i = 0; i < n; ++i) {
            int tmp = par[i][j - 1];
            if(tmp != -1) par[i][j] = par[tmp][j - 1];
        }
    }
    auto lca = [&](int u, int v) {
        if(dep[u] > dep[v]) swap(u, v);
        int gap = dep[v] - dep[u];
        for(int i = 0; i < 18 && gap > 0; ++i, gap >>= 1) {
            if(gap & 1) v = par[v][i];
        }

        if(u != v) {
            for(int i = 18 - 1; i >= 0; --i) {
                if(par[u][i] != par[v][i]) {
                    u = par[u][i];
                    v = par[v][i];
                }
            }
            u = par[u][0];
        }
        return u;
    };
    auto dis = [&](int u, int v) {
        return cost[u] + cost[v] - 2 * cost[lca(u, v)];
    };

    vector<int> sz(n);
    vector<char> visit(n, false);
    auto getsz = [&](auto&& self, int cur, int pre) -> int {
        sz[cur] = 1;
        for(auto [nxt, _] : g[cur]) {
            if(nxt == pre || visit[nxt]) continue;
            sz[cur] += self(self, nxt, cur);
        }
        return sz[cur];
    };
    auto getcen = [&](auto&& self, int cur, int pre, int size) -> int {
        for(auto [nxt, _] : g[cur]) {
            if(nxt == pre || visit[nxt]) continue;
            if(sz[nxt] > size / 2) return self(self, nxt, cur, size);
        }
        return cur;
    };

    vector<int> cenPar(n);
    auto centroid = [&](auto&& self, int cur, int pre) -> void {
        int sz = getsz(getsz, cur, -1);
        int cen = getcen(getcen, cur, -1, sz);

        visit[cen] = true;
        cenPar[cen] = pre;

        for(auto [nxt, _] : g[cen]) {
            if(nxt == pre || visit[nxt]) continue;
            self(self, nxt, cen);
        }
    };
    centroid(centroid, 0, -1);

    int q;
    cin >> q;
    vector<pair<int, int>> qList(q);
    for(auto& v : qList) {
        cin >> v.first;
        if(v.first == 1) cin >> v.second;
    }

    vector<multiset<int>> childCosts(n);
    vector<map<int, multiset<int>>> subtree(n);
    vector<char> white(n, false);
    int numWhite = 0;
    vector<int> curMx(n, -INF);
    multiset<int> res;
    for(int i = 0; i < n; ++i) {
        subtree[i].insert({ i, {} });
        childCosts[i].insert(-INF);
        res.insert(-INF);

        if(cenPar[i] != -1) {
            subtree[cenPar[i]].insert({ i, {} });
            childCosts[cenPar[i]].insert(-INF);
        }
    }
    auto flipNode = [&](int idx) {
        int cur = idx;
        white[idx] = !white[idx];
        if(white[idx] == false) numWhite--;
        else numWhite++;

        int last = cur;
        while(cur != -1) {
            int cost = dis(idx, cur);

            auto& curSubTree = subtree[cur].find(last)->second;
            int oldCost = -INF;
            if(curSubTree.size() > 0) oldCost = *prev(curSubTree.end());

            if(white[idx] == false) {
                curSubTree.erase(curSubTree.find(cost));
            } else {
                curSubTree.insert(cost);
            }

            int newCost = -INF;
            if(curSubTree.size() > 0) newCost = *prev(curSubTree.end());

            if(oldCost != newCost) {
                childCosts[cur].erase(childCosts[cur].find(oldCost));
                childCosts[cur].insert(newCost);
            }

            int oldMx = curMx[cur];
            int newMx = -INF;
            if(childCosts[cur].size() >= 2) {
                auto v1 = prev(childCosts[cur].end());
                auto v2 = prev(v1);
                newMx = max(newMx, *v1 + *v2);
            }
            curMx[cur] = newMx;

            if(oldMx != newMx) {
                res.erase(res.find(oldMx));
                res.insert(newMx);
            }

            last = cur;
            cur = cenPar[cur];
        }
    };

    for(int i = 0; i < n; ++i) {
        flipNode(i);
    }

    for(auto [a, b] : qList) {
        //cout << cnt;
        //cnt++;
        if(a == 1) {
            flipNode(b - 1);
        } else {
            int r = max(-1, *prev(res.end()));
            if(numWhite > 0) r = max(r, 0);
            cout << r << "\n";
        }
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
