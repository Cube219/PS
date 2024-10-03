#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cassert>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, k, t;
    cin >> n >> k >> t;
    vector<pair<int, int>> uv(k);
    for(auto& [u, v] : uv){
        cin >> u >> v;
        u--;
        v--;
    }
    vector<int> d(n);
    for (auto& v : d) cin >> v;
    vector<vector<int>> g(n);
    vector<int> in(n, 0);
    for(auto& [u, v] : uv) {
        if (d[u] > d[v]) swap(u, v);
        g[u].push_back(v);
        in[v]++;
    }

    vector<int> dir(n, -1);
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        v--;

        sort(g[i].begin(), g[i].end());
        if (v != -2)  {
            for (int j = 0; j < g[i].size(); ++j){
                if(g[i][j] == v)
                {
                    dir[i] = j;
                    break;
                }
            }
            assert(dir[i] != -1);
        }
    }

    vector<int> cnt(n, 0);
    queue<int> q;
    int st;
    for (int i = 0; i < n; ++i) {
        if(d[i] == 1) {
            assert(in[i] == 0);
            st = i;
            cnt[i] = t - 1;
            break;
        }
    }

    for(int i = 0; i < n; ++i) {
        if (in[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int cur = q.front();
        q.pop();

        int sz = g[cur].size();
        auto& child = g[cur];
        if (sz == 0) continue;

        for (int i = 0; i < sz; ++i) {
            cnt[child[(dir[cur] + i) % sz]] += cnt[cur] / sz;
        }
        cnt[cur] %= sz;
        for(int i = 0; i < cnt[cur]; ++i) {
            cnt[child[(dir[cur] + i) % sz]]++;
        }
        dir[cur] = (dir[cur] + cnt[cur]) % sz;


        for(int nxt : child) {
            in[nxt]--;
            if (in[nxt] == 0) q.push(nxt);
        }
    }

    int cur = st;
    while(g[cur].size() > 0) {
        cur = g[cur][dir[cur]];
    }

    cout << cur + 1;
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