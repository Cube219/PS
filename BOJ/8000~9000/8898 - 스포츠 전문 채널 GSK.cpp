#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
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
    vector<int> s(n), d(n);
    for(auto& v : s) cin >> v;
    for(auto& v : d) cin >> v;
    vector<vector<int>> g(n);
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            int t;
            cin >> t;

            if(s[i] + d[i] + t <= s[j]) {
                g[i].push_back(j);
            }
            if(s[j] + d[j] + t <= s[i]) {
                g[j].push_back(i);
            }
        }
    }

    vector<int> a(n, -1), b(n, -1), level(n);
    auto initLevel = [&]() {
        queue<int> q;
        for(int i = 0; i < n; ++i) {
            if(a[i] == -1) {
                q.push(i);
                level[i] = 0;
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
            if(a[i] == -1 && dfs(dfs, i)) f++;
        }
        if(f == 0) break;
        flow += f;
    }

    // req: psbipartite
    auto cover = [&]() {
        vector<char> visitL(n, true), visitR(n, false);
        for(int i = 0; i < n; ++i) if(a[i] != -1) visitL[i] = false;
        queue<int> q;
        for(int i = 0; i < n; ++i) if(visitL[i]) q.push(i);
        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            visitL[cur] = true;
            for(int nxt : g[cur]) {
                if(!visitR[nxt] && b[nxt] != -1) {
                    visitR[nxt] = true;
                    q.push(b[nxt]);
                }
            }
        }
        vector<int> res;
        for(int i = 0; i < n; ++i) if(!visitL[i]) res.push_back(i);
        for(int i = 0; i < n; ++i) if(visitR[i]) res.push_back(i + n);
        return res;
    };

    auto res = cover();
    cout << n - res.size() << "\n";
    vector<char> isCover(n, false);
    for(int v : res) {
        if(v >= n) v -= n;
        isCover[v] = true;
    }

    for(int i = 0; i < n; ++i) {
        if(!isCover[i]) cout << i + 1 << " ";
    }

    cout << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
