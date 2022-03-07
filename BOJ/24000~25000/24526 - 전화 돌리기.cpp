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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> in(n, 0);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[b].push_back(a);
        in[a]++;
    }

    int res = 0;
    queue<int> q;
    for(int i = 0; i < n; ++i) {
        if(in[i] == 0) q.push(i);
    }
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        res++;
        for(int nxt : g[cur]) {
            in[nxt]--;
            if(in[nxt] == 0) q.push(nxt);
        }
    }

    cout << res;
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
