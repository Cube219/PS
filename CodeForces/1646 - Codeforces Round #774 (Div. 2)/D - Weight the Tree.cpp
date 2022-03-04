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
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    if(n == 2) {
        cout << "2 2\n";
        cout << "1 1\n";
        return;
    }

    vector<ll> use(n, 0), notUse(n, 0);
    vector<ll> useSum(n, 0), notUseSum(n, 0);
    vector<vector<int>> selectNotUse = g;

    auto dfs = [&](auto&& self, int cur, int pre) -> void {
        for(int i = 0; i < g[cur].size(); ++i) {
            int nxt = g[cur][i];
            if(nxt == pre) continue;

            self(self, nxt, cur);
            // not use에서 어떤게 더 크냐
            bool selectUse;
            if(use[nxt] > notUse[nxt]) {
                selectUse = true;
            } else if(use[nxt] < notUse[nxt]) {
                selectUse = false;
            } else {
                if(useSum[nxt] < notUseSum[nxt]) {
                    selectUse = true;
                } else {
                    selectUse = false;
                }
            }

            if(selectUse) {
                notUse[cur] += use[nxt];
                notUseSum[cur] += useSum[nxt];
                selectNotUse[cur][i] = 0;
            } else {
                notUse[cur] += notUse[nxt];
                notUseSum[cur] += notUseSum[nxt];
                selectNotUse[cur][i] = 1;
            }

            use[cur] += notUse[nxt];
            useSum[cur] += notUseSum[nxt];
        }

        use[cur]++;
        useSum[cur] += g[cur].size();
        notUseSum[cur]++;
    };
    dfs(dfs, 0, -1);

    vector<char> isUse(n);
    auto dfs2 = [&](auto&& self, int cur, int pre, char f) -> void {
        isUse[cur] = f;

        for(int i = 0; i < g[cur].size(); ++i) {
            int nxt = g[cur][i];
            if(nxt == pre) continue;

            if(f == true) {
                self(self, nxt, cur, false);
            } else if(selectNotUse[cur][i] == 0) {
                self(self, nxt, cur, true);
            } else {
                self(self, nxt, cur, false);
            }
        }
    };


    if(use[0] > notUse[0]) {
        dfs2(dfs2, 0, -1, true);
    } else if(use[0] < notUse[0]) {
        dfs2(dfs2, 0, -1, false);
    } else {
        if(useSum[0] < notUseSum[0]) {
            dfs2(dfs2, 0, -1, true);
        } else {
            dfs2(dfs2, 0, -1, false);
        }
    }

    int cnt = 0;
    ll sum = 0;
    vector<ll> res(n, 0);

    for(int i = 0; i < n; ++i) {
        if(isUse[i]) {
            cnt++;
            continue;
        }

        res[i] = 1;
        for(int nxt : g[i]) {
            if(isUse[nxt]) res[nxt]++;
        }
    }
    for(int i = 0; i < n; ++i) {
        sum += res[i];
    }



    cout << cnt << " " << sum << "\n";
    for(ll v : res) cout << v << " ";
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
