#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
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
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int m;
    cin >> m;
    vector<int> p(m), l(m), q(m);
    vector<vector<int>> charge(n);
    for(int i = 0; i < m; ++i) {
        cin >> p[i] >> l[i];
        p[i]--;
        charge[p[i]].push_back(i);
    }

    struct Node
    {
        bool isReq;
        int len, idx;
        bool operator<(const Node& rhs) const
        {
            return len < rhs.len;
        }
    };

    vector<int> par(n, -1);
    auto dfs2 = [&](auto&& self, int cur, int pre) -> void {
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;
            par[nxt] = cur;
            self(self, nxt, cur);
        }
    };
    dfs2(dfs2, 0, -1);

    auto up = [&](int cur, int step) {
        for(int i = 0; i < step; ++i) {
            cur = par[cur];
        }
        return cur;
    };

    bool pos = true;
    auto dfs = [&](auto&& self, int cur, int pre) -> Node {
        multiset<Node> reqList, lenList;
        for(int nxt : g[cur]) {
            if(nxt == pre) continue;

            Node res = self(self, nxt, cur);
            if(pos == false) return {};

            if(res.isReq) {
                if(res.len == 1) {
                    q[res.idx] = cur;
                } else {
                    res.len--;
                    reqList.insert(res);
                }
            } else {
                res.len++;
                lenList.insert(res);
            }
        }

        for(int idx : charge[cur]) {
            reqList.insert({ true, l[idx], idx });
        }

        Node upReq = { true, -1, -1 };
        while(reqList.size() > 0) {
            auto it = prev(reqList.end());
            auto it2 = lenList.lower_bound({ true, it->len, -1 });
            if(it2 == lenList.end()) {
                if(upReq.len != -1) {
                    pos = false;
                    return {};
                }
                upReq = *it;
                reqList.erase(it);
                continue;
            }
            q[it->idx] = up(it2->idx, it2->len - it->len); // 올리기
            lenList.erase(it2);
            reqList.erase(it);
        }
        if(upReq.len != -1) {
            return upReq;
        }

        Node mx = { false, 0, cur };

        for(auto& it : lenList) {
            if(mx.len < it.len) {
                mx.len = it.len;
                mx.idx = it.idx;
            }
        }
        return mx;
    };
    auto res = dfs(dfs, 0, -1);

    if(res.isReq || !pos) {
        cout << "NO";
        return;
    }

    cout << "YES\n";
    for(int i = 0; i < m; ++i) {
        cout << p[i] + 1 << " " << q[i] + 1 << "\n";
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
