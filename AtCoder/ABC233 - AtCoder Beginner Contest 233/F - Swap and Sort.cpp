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
    vector<int> d(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    int q;
    cin >> q;
    vector<vector<int>> g(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> nxt(n + 1, vector<int>(n + 1, -1));
    unordered_map<ll, int> mp;
    for(int i = 0; i < q; ++i) {
        ll a, b;
        cin >> a >> b;
        g[a][b] = 1;
        g[b][a] = 1;
        mp.insert({ a << 32 | b, i + 1 });
        mp.insert({ b << 32 | a, i + 1 });
    }
    for(int i = 1; i <= n; ++i) {
        g[i][i] = 0;
    }
    for(int k = 1; k <= n; ++k) {
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(g[i][j] > g[i][k] + g[k][j]) {
                    g[i][j] = g[i][k] + g[k][j];
                    nxt[i][j] = k;
                }
            }
        }
    }

    bool f = true;
    vector<int> res, pos(n + 1);
    for(int i = 1; i <= n; ++i) {
        pos[d[i]] = i;
    }
    for(int i = 1; i <= n; ++i) {
        int cost = g[pos[i]][i];
        if(cost == INF) {
            f = false;
            break;
        }

        int curpos = pos[i];
        pos[d[i]] = curpos;
        pos[i] = i;
        swap(d[i], d[curpos]);
        vector<int> tmp;
        int c = curpos;
        tmp.push_back(c);
        auto path = [&](auto&& self, int st, int ed) ->void {
            if(nxt[st][ed] == -1) return;
            self(self, st, nxt[st][ed]);
            tmp.push_back(nxt[st][ed]);
            self(self, nxt[st][ed], ed);
        };
        path(path, c, i);
        tmp.push_back(i);
        if(c != i) {
            for(int j = 0; j < (int)tmp.size() - 1; ++j) {
                ll a = tmp[j];
                ll b = tmp[j + 1];
                res.push_back(mp.find(a << 32 | b)->second);
            }
            for(int j = (int)tmp.size() - 2; j >= 1; --j) {
                ll a = tmp[j];
                ll b = tmp[j - 1];
                res.push_back(mp.find(a << 32 | b)->second);
            }
        }
    }

    if(f == false) {
        cout << "-1";
    } else {
        cout << res.size() << "\n";
        for(int v : res) cout << v << " ";
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
