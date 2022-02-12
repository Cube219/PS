#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
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
    vector<vector<int>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end());
        g[i].erase(unique(g[i].begin(), g[i].end()), g[i].end());
    }

    vector<int> curList, res(n, -1), cnt(n, 0);
    curList.push_back(0);
    for(int step = 0; step < n && curList.size() > 0; ++step) {
        for(int cur : curList) {
            cnt[cur] = -1;
            res[cur] = step;
        }

        for(int cur : curList) {
            for(int nxt : g[cur]) {
                if(cnt[nxt] == -1) continue;
                cnt[nxt]++;
            }
        }
        vector<int> nxtList;
        for(int i = 0; i < n; ++i) {
            if(cnt[i] != -1 && cnt[i] < curList.size()) {
                nxtList.push_back(i);
            }
        }

        for(int cur : curList) {
            for(int nxt : g[cur]) {
                if(cnt[nxt] == -1) continue;
                cnt[nxt] = 0;
            }
        }
        curList = nxtList;
    }

    for(int v : res) cout << v << "\n";
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
