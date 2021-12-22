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
    int n, h;
    cin >> n >> h;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> leaf;
    auto dfs = [&](auto&& self, int cur, int pre)->void {
        if(g[cur].size() == 1) leaf.push_back(cur);
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;
            self(self, nxt, cur);
        }
    };
    dfs(dfs, 0, -1);

    int lnum = leaf.size();
    cout << (lnum + 1) / 2 << "\n";
    for(int i = 0; i < lnum / 2; ++i) {
        cout << leaf[i] << " " << leaf[i + lnum / 2] << "\n";
    }
    if(lnum & 1) cout << leaf[0] << " " << leaf.back() << "\n";
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
