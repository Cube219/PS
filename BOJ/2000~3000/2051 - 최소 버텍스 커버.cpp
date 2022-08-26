#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
#include <chrono>
#include <functional>
#include <queue>
#include <random>
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
    for(int i = 0; i < n; ++i) {
        int num; cin >> num;
        for(int j = 0; j < num; ++j) {
            int v; cin >> v;
            g[i].push_back(v - 1);
        }
    }

    vector<int> a(n, -1), b(m, -1), level(n);
    auto initLevel = [&]() {
        queue<int> q;
        for(int i = 0; i < n; ++i) {
            if(a[i] == -1) {
                level[i] = 0;
                q.push(i);
            } else level[i] = -1;
        }
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            for(int nxt : g[cur]) {
                if(b[nxt] != -1 && level[b[nxt]] == -1) {
                    level[b[nxt]] = level[cur] + 1;
                    q.push(b[nxt]);
                }
            }
        }
    };
    auto dfs = [&](auto&& self, int cur) -> bool {
        for(int nxt : g[cur]) {
            if(b[nxt] == -1 || (level[b[nxt]] == level[cur] + 1 && self(self, b[nxt]))) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
        return false;
    };
    int flow = 0;
    while(1) {
        initLevel();
        int f = 0;
        for(int i = 0; i < n; ++i) {
            if(a[i] == -1) f += dfs(dfs, i);
        }
        if(f == 0) break;
        flow += f;
    }

    auto cover = [&]() {
        vector<char> visitA(n, false), visitB(m, false);
        queue<int> q;
        for(int i = 0; i < n; ++i) if(a[i] == -1) q.push(i);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            visitA[cur] = true;
            for(int nxt : g[cur]) {
                if(b[nxt] != -1 && !visitB[nxt]) {
                    visitB[nxt] = true;
                    q.push(b[nxt]);
                }
            }
        }
        vector<int> res;
        for(int i = 0; i < n; ++i) if(!visitA[i]) res.push_back(i);
        for(int i = 0; i < m; ++i) if(visitB[i]) res.push_back(n + i);
        return res;
    };
    auto res = cover();
    vector<int> ares, bres;
    for(int v : res) {
        if(v < n) ares.push_back(v + 1);
        else bres.push_back(v - n + 1);
    }
    cout << res.size() << "\n";
    cout << ares.size() << " ";
    for(int v : ares) cout << v << " ";
    cout << "\n";
    cout << bres.size() << " ";
    for(int v : bres) cout << v << " ";
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
