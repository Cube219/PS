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
    struct Nxt { int nxt, cost; };
    vector<Nxt> g(n);
    vector<vector<Nxt>> rev(n);
    for(int i = 0; i < n; ++i) {
        int v, c;
        cin >> v >> c;
        v--;
        g[i] = { v, c };
        rev[v].push_back({ i, c });
    }

    vector<int> r(n);
    for(auto& v : r) cin >> v;

    int m;
    cin >> m;
    vector<int> a(m);
    vector<char> hasA(n, false);
    for(auto& v : a) {
        cin >> v; v--;
        hasA[v] = true;
    }

    struct Cycle
    {
        int n, st, cur;
        vector<ll> sum;
        ll mvCost;
    };
    vector<Cycle> cycles;
    vector<int> cycleIdx(n, -1), idxInCycle(n, -1);

    vector<int> st;
    vector<char> visit(n, false);
    auto dfs = [&](auto&& self, int cur) -> void {
        st.push_back(cur);
        visit[cur] = true;

        auto [nxt, _] = g[cur];
        if(cycleIdx[nxt] != -1) return; // Already find cycle

        if(!visit[nxt]) self(self, nxt);
        else {
            // Find cycle
            int sz = 0;
            int i = st.size() - 1;
            while(i > 0 && st[i] != nxt) i--;
            if(st[i] != nxt) return; // Already visited

            while(1) {
                int v = st.back(); st.pop_back();
                sz++;
                cycleIdx[v] = cycles.size();
                if(v == nxt) break;
            }

            cycles.emplace_back();
            auto& c = cycles.back();
            c.n = sz;
            c.st = nxt;
            c.cur = -1;
        }
    };
    for(int i = 0; i < n; ++i) {
        if(!visit[i]) {
            st.clear();
            dfs(dfs, i);
        }
    }

    // Give indices per cycle
    for(auto& c : cycles) {
        int cur = c.st;
        idxInCycle[cur] = 0;
        c.sum.resize(c.n * 2, 0);
        for(int i = 1; i < c.n * 2; ++i) {
            auto [nxt, cost] = g[cur];
            if(i < c.n) idxInCycle[nxt] = i;
            c.sum[i] = c.sum[i - 1] + cost;

            cur = nxt;
        }
    }

    // Calculate out-cycle vertices
    vector<ll> res(n, 0);
    auto dfs2 = [&](auto&& self, int cur, ll cost) -> void {
        if(cost > 0) res[cur] = cost;
        if(hasA[cur] && cost < 0) cost = 0;

        for(auto [nxt, c] : rev[cur]) {
            self(self, nxt, cost + c);
        }
    };
    for(auto& c : cycles) {
        int cur = c.st;
        for(int i = 0; i < c.n; ++i) {
            for(auto [nx, _] : rev[cur]) {
                if(cycleIdx[nx] == -1) { // Out-cycle
                    dfs2(dfs2, nx, -LNF);
                }
            }
            cur = g[cur].nxt;
        }
    }

    for(int i = 0; i < m; ++i) {
        int v = a[i];
        if(cycleIdx[v] == -1) continue;

        auto& c = cycles[cycleIdx[v]];
        if(c.cur == -1) { // Initial move
            c.cur = v;
            c.st = v;
        } else {
            int st = idxInCycle[c.cur];
            int ed = idxInCycle[v];
            if(st > ed) ed += c.n;

            c.mvCost += c.sum[ed] - c.sum[st];
            c.cur = v;
        }
    }

    // Recalculate if the cycle is colored
    fill(visit.begin(), visit.end(), false);
    auto dfs3 = [&](auto&& self, int cur, ll cost) -> void {
        visit[cur] = true;
        res[cur] = cost;

        for(auto [nxt, c] : rev[cur]) {
            if(!visit[nxt]) {
                self(self, nxt, cost + c);
            }
        }
    };
    for(auto& c : cycles) {
        if(c.cur == -1) continue;
        dfs3(dfs3, c.st, c.mvCost);
    }

    for(int i = 0; i < n; ++i) {
        cout << res[i] * r[i] << "\n";
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
