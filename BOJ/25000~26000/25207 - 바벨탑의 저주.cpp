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
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
    }
    for(int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end());
    }

    vector<int> num(n, 0);
    auto dfs = [&](auto&& self, int cur) -> int {
        num[cur]++;
        for(int nxt : g[cur]) {
            num[cur] += self(self, nxt);
        }
        return num[cur];
    };
    dfs(dfs, 0);

    auto order = [&](auto&& self, int cur, vector<int>& rec, vector<char>& isDown, bool isRev) -> void {
        rec.push_back(a[cur]);
        if(isRev == false) {
            for(int i = 0; i < g[cur].size(); ++i) {
                isDown.push_back(true);
                self(self, g[cur][i], rec, isDown, isRev);
            }
        } else {
            for(int i = g[cur].size() - 1; i >= 0; --i) {
                isDown.push_back(true);
                self(self, g[cur][i], rec, isDown, isRev);
            }
        }
        isDown.push_back(false);
    };

    vector<char> res(n, false);
    int cnt = 0;
    auto dfs2 = [&](auto&& self, int cur) -> void {
        if(g[cur].size() == 0) {
            res[cur] = true;
            cnt++;
            return;
        }

        for(int nxt : g[cur]) {
            self(self, nxt);
        }

        auto& child = g[cur];

        int l = 0, r = child.size() - 1;
        bool ck = true;
        while(l < r) {
            if(num[child[l]] != num[child[r]]) {
                ck = false;
                break;
            }
            l++; r--;
        }
        if(ck == true) {
            l = 0;
            r = child.size() - 1;
            vector<int> lOrder, rOrder;
            vector<char> lIsDown, rIsDown;
            while(l < r) {
                lOrder.clear();
                rOrder.clear();
                lIsDown.clear();
                rIsDown.clear();
                order(order, child[l], lOrder, lIsDown, false);
                order(order, child[r], rOrder, rIsDown, true);
                for(int i = 0; i < lOrder.size(); ++i) {
                    if(lOrder[i] != rOrder[i]) {
                        ck = false;
                        break;
                    }
                }
                for(int i = 0; i < lIsDown.size(); ++i) {
                    if(lIsDown[i] != rIsDown[i]) {
                        ck = false;
                        break;
                    }
                }
                if(ck == false) break;
                l++; r--;
            }

            if(l == r && ck == true) ck = res[child[l]];
        }
        res[cur] = ck;
        if(ck) cnt++;
    };
    dfs2(dfs2, 0);

    cout << cnt << "\n";
    for(int i = 0; i < n; ++i) {
        if(res[i]) cout << i + 1 << " ";
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
