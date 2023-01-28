#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
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
    vector<int> g(n);
    vector<vector<int>> g2(n);
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        v--;
        g[i] = v;
        g2[v].push_back(i);
    }

    vector<char> isCycle(n, false), visit(n, false);
    vector<bool> is1(n);
    vector<int> st;
    vector<vector<int>> cycles;
    // ret: isReverse?
    auto dfs = [&](auto&& self, int cur, bool curIs1) -> bool {
        st.push_back(cur);
        visit[cur] = true;
        is1[cur] = curIs1;

        int nxt = g[cur];
        bool rev = false;
        if(visit[nxt]) {
            vector<int> c;
            while(!st.empty()) {
                int top = st.back(); st.pop_back();
                c.push_back(top);
                if(top == nxt) break;
            }
            if(c.back() == nxt) {
                for(int v : c) isCycle[v] = true;
                cycles.push_back(move(c));
            } else {
                if(is1[nxt] == is1[cur]) {
                    is1[cur] = !is1[cur];
                    rev = true;
                }
            }
        } else {
            rev = self(self, nxt, !curIs1);
            if(rev) is1[cur] = !is1[cur];
        }

        return rev;
    };

    for(int i = 0; i < n; ++i) {
        if(visit[i]) continue;

        st.clear();
        dfs(dfs, i, false);
    }

    vector<int> num0(n, 0), num1(n, 0);
    auto dfs2 = [&](auto&& self, int cur) -> void {
        if(is1[cur]) num1[cur]++;
        else num0[cur]++;
        for(int nxt : g2[cur]) {
            if(isCycle[nxt]) continue;

            self(self, nxt);
            num0[cur] += num0[nxt];
            num1[cur] += num1[nxt];
        }
    };
    for(int i = 0; i < n; ++i) {
        if(!isCycle[i]) continue;

        dfs2(dfs2, i);
    }

    vector<vector<int>> odd, even;
    for(auto& c : cycles) {
        if(c.size() & 1) odd.push_back(move(c));
        else even.push_back(move(c));
    }

    vector<int> res;
    if(odd.size() == 0) {
        int mx = 0;
        for(auto& c : even) {
            int e0 = 0, e1 = 0;
            for(int v : c) {
                e0 += num0[v];
                e1 += num1[v];
            }
            mx += max(e0, e1);
        }
        for(auto& c : even) {

            int my0 = 0, my1 = 0;
            for(int v : c) {
                my0 += num0[v];
                my1 += num1[v];
            }

            auto dfs3 = [&](auto&& self, int cur) -> void {
                for(int nxt : g2[cur]) {
                    if(isCycle[nxt]) continue;

                    int new0 = my0 - num0[nxt] + num1[nxt];
                    int new1 = my1 - num1[nxt] + num0[nxt];
                    if(max(new0, new1) + mx >= m) res.push_back(nxt);

                    self(self, nxt);
                }
            };

            mx -= max(my0, my1);
            for(int v : c) dfs3(dfs3, v);
            mx += max(my0, my1);
        }
    } else if(odd.size() == 1) {
        int evenMx = 0;
        int odd0 = 0, odd1 = 0;
        for(auto& c : even) {
            int e0 = 0, e1 = 0;
            for(int v : c) {
                e0 += num0[v];
                e1 += num1[v];
            }
            evenMx += max(e0, e1);
        }
        for(int v : odd[0]) {
            odd0 += num0[v];
            odd1 += num1[v];
        }

        for(int cur : odd[0]) {
            if(max(odd0, odd1) + evenMx >= m) res.push_back(cur);
            odd0 -= num0[cur] - num1[cur];
            odd1 -= num1[cur] - num0[cur];
        }
    }

    if(res.size() == 0) cout << "-1";
    else {
        sort(res.begin(), res.end());
        cout << res.size() << "\n";
        for(int v : res) cout << v + 1 << " ";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input2.txt", "r", stdin);
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
