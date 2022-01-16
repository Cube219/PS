#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <unordered_map>
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
    vector < vector<pair<int, int>>> g(n);
    unordered_map<ll, int> mp;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back({ b, 0 });
        g[b].push_back({ a, 1 });

        if(a > b) swap(a, b);
        mp[(ll)a << 32 | (ll)b] = i;
    }

    vector<int> num0(n, 0), num1(n, 0);
    vector<int> num0rt(n, 0), num1rt(n, 0);
    auto dfs = [&](auto&& self, int cur, int pre) -> pair<int, int> {
        for(auto [nxt, dir] : g[cur]) {
            if(nxt == pre) continue;

            num0rt[nxt] = num0rt[cur];
            num1rt[nxt] = num1rt[cur];
            if(dir == 0) {
                num0rt[nxt]++;
                num0[cur]++;
            } else {
                num1rt[nxt]++;
                num1[cur]++;
            }
            auto ret = self(self, nxt, cur);

            num0[cur] += ret.first;
            num1[cur] += ret.second;
        }
        return { num0[cur], num1[cur] };
    };
    dfs(dfs, 0, -1);

    int mn = INF, rt = -1;

    for(int i = 0; i < n; ++i) {
        int cnt1 = num1[0] - num1rt[i] + num0rt[i];
        if(mn > cnt1) {
            mn = cnt1;
            rt = i;
        }
    }

    vector<int> res(n - 1, 0);
    auto dfs2 = [&](auto&& self, int cur, int pre) -> void {
        for(auto [nxt, dir] : g[cur]) {
            if(nxt == pre) continue;

            if(dir == 1) {
                ll a = cur;
                ll b = nxt;
                if(a > b) swap(a, b);

                int idx = mp[a << 32 | b];
                res[idx] = 1;
            }
            self(self, nxt, cur);
        }
    };
    dfs2(dfs2, rt, -1);

    for(int i = 0; i < n - 1; ++i) {
        cout << res[i];
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
