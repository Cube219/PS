#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n = 1, q;
    struct Nxt { int nxt, cost; };
    vector<vector<Nxt>> g(1);
    cin >> q;

    struct Query { int st, ed, num; };
    vector<Query> ql;
    for(int i = 0; i < q; ++i) {
        string str;
        int a, b;
        cin >> str >> a >> b;
        if(str[0] == 'A') {
            a--;
            g.push_back({});
            g[a].push_back({ n++, b });
        } else {
            ql.push_back({ a - 1, b - 1, n - 1 });
        }
    }

    vector<int> cost(n), st(n), ed(n);
    int num = 0;
    auto dfs = [&](auto&& self, int cur, int c) -> void {
        st[cur] = num++;
        cost[cur] = c;
        for(auto [nxt, cc] : g[cur]) {
            self(self, nxt, c ^ cc);
        }
        ed[cur] = num - 1;
    };
    dfs(dfs, 0, 0);

    struct Trie
    {
        int nxt[2];
        set<int> idx;
        Trie()
        {
            nxt[0] = nxt[1] = -1;
        }
    };
    vector<Trie> t;
    t.reserve(4000000);
    t.push_back({});
    auto insert = [&](int v, int idx) {
        int cur = 0;
        for(int i = 31 - 1; i >= 0; --i) {
            int bit = ((1 << i) & v) > 0 ? 1 : 0;

            if(t[cur].nxt[bit] == -1) {
                t[cur].nxt[bit] = t.size();
                t.push_back({});
            }
            cur = t[cur].nxt[bit];
            t[cur].idx.insert(idx);
        }
    };
    auto query = [&](int v, int st, int ed) {
        int cur = 0;
        int res = 0;
        for(int i = 31 - 1; i >= 0; --i) {
            int bit = ((1 << i) & v) > 0 ? 1 : 0;

            int nxt = t[cur].nxt[1 - bit];
            if(nxt != -1) {
                auto it = t[nxt].idx.lower_bound(st);
                if(it != t[nxt].idx.end() && *it <= ed) {
                    res |= 1 << i;
                    cur = nxt;
                } else {
                    cur = t[cur].nxt[bit];
                }
            } else {
                cur = t[cur].nxt[bit];
            }
        }
        return res;
    };
    insert(0, 0);

    int curNum = 0;
    for(auto [s, e, num] : ql) {
        for(; curNum < num; curNum++) {
            insert(cost[curNum + 1], st[curNum + 1]);
        }

        int res = query(cost[s], st[e], ed[e]);
        cout << res << "\n";
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
