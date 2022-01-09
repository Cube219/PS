#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> c(n), cnum(k, 0);
    for(auto& v : c) {
        cin >> v;
        v--;
        cnum[v]++;
    }

    vector<int> sz(n);
    vector<char> visit(n, false);
    auto getsz = [&](auto&& self, int cur, int pre) -> int {
        sz[cur] = 1;
        for(int nxt : g[cur]) {
            if(nxt == pre || visit[nxt]) continue;
            sz[cur] += self(self, nxt, cur);
        }
        return sz[cur];
    };
    auto getcen = [&](auto&& self, int cur, int pre, int size) -> int {
        for(int nxt : g[cur]) {
            if(nxt == pre || visit[nxt]) continue;
            if(sz[nxt] > size / 2) return self(self, nxt, cur, size);
        }
        return cur;
    };

    int res = INF;
    vector<char> mark(k, false);
    vector<int> par(n);
    vector<vector<int>> vlist(k);

    auto search = [&](auto&& self, int cur, int pre) -> void {
        vlist[c[cur]].push_back(cur);
        cnum[c[cur]]--;
        par[cur] = pre;
        for(int nxt : g[cur]) {
            if(nxt == pre || visit[nxt]) continue;
            self(self, nxt, cur);
        }
    };

    auto clear = [&](auto&& self, int cur, int pre) -> void {
        vlist[c[cur]].clear();
        cnum[c[cur]]++;
        mark[c[cur]] = false;
        for(int nxt : g[cur]) {
            if(nxt == pre || visit[nxt]) continue;
            self(self, nxt, cur);
        }
    };

    auto centroid = [&](auto&& self, int cur, int pre) -> void {
        int sz = getsz(getsz, cur, -1);
        int cen = getcen(getcen, cur, -1, sz);

        visit[cen] = true;
        search(search, cen, -1);

        vector<int> st;
        int curres = 0;
        st.push_back(c[cen]);
        mark[c[cen]] = true;
        while(st.size() > 0) {
            int curc = st.back();
            st.pop_back();
            curres++;
            if(cnum[curc] > 0) {
                curres = INF;
                break;
            }

            for(int v : vlist[curc]) {
                int pv = par[v];
                if(pv == -1 || visit[pv] || mark[c[pv]]) continue;
                st.push_back(c[pv]);
                mark[c[pv]] = true;
            }
        }
        res = min(res, curres);

        clear(clear, cen, -1);

        for(int nxt : g[cen]) {
            if(nxt == pre || visit[nxt]) continue;
            self(self, nxt, cen);
        }
    };
    centroid(centroid, 0, -1);

    cout << res - 1;
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
