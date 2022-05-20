#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
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
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
    }
    vector<char> has(n, false);
    int s;
    cin >> s;
    for(int i = 0; i < s; ++i) {
        int v;
        cin >> v;
        v--;
        has[v] = true;
    }

    bool pos = false;
    vector<char> visit(n, false);
    queue<int> q;
    q.push(0);
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        if(has[cur]) continue;
        if(g[cur].size() == 0) {
            pos = true;
            break;
        }

        for(int nxt : g[cur]) {
            if(visit[nxt]) continue;

            visit[nxt] = true;
            q.push(nxt);
        }
    }

    if(pos == true) cout << "yes";
    else cout << "Yes";
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
