#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct SegTree
{
    int n;
    vector<int> t;

    SegTree(int _n)
    {
        n = _n;
        t.resize(n * 2, 0);
    }

    vector<int> query(int l, int r)
    {
        l += n;
        r += n + 1;
        vector<int> res;
        while(l < r) {
            if(l & 1) res.push_back(t[l++]);
            if(r & 1) res.push_back(t[--r]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
};


void solve()
{
    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    vector<vector<int>> g(n * 2);
    SegTree sg(n);
    int idx = 0;
    for(int i = 0; i < n; ++i) {
        sg.t[n + i] = idx++;
    }
    for(int i = n - 1; i > 0; --i) {
        sg.t[i] = idx++;
        int u = sg.t[i * 2];
        int v = sg.t[i];
        g[u].push_back(v);
        u = sg.t[i * 2 + 1];
        g[u].push_back(v);
    }

    vector<int> l(n), r(n);
    for(int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        l[i]--; r[i]--;
        auto list = sg.query(l[i], r[i]);
        for(int u : list) g[u].push_back(i);
    }

    vector<int> dep(n * 2, 0), st, finish(n * 2, false), sccIdx(n * 2);
    vector<vector<int>> sccs;
    int dNum = 0;

    auto scc_dfs = [&](auto&& self, int cur) -> int {
        dep[cur] = ++dNum;
        st.push_back(cur);

        int ret = dep[cur];
        for(int nxt : g[cur]) {
            if(dep[nxt] == 0) ret = min(ret, self(self, nxt));
            else if(finish[nxt] == false) ret = min(ret, dep[nxt]);
        }

        if(ret == dep[cur]) {
            sccs.push_back({});
            auto& scc = sccs.back();
            while(1) {
                int top = st.back();
                st.pop_back();

                scc.push_back(top);
                sccIdx[top] = (int)sccs.size() - 1;
                finish[top] = true;

                if(top == cur) break;
            }
        }
        return ret;
    };
    for(int i = 0; i < n * 2; ++i) {
        if(dep[i] == 0) scc_dfs(scc_dfs, i);
    }

    vector<int> dp(sccs.size(), 0);
    vector<int> in(sccs.size(), 0);
    vector<vector<int>> rev(sccs.size());
    for(int i = 0; i < n * 2; ++i) {
        if(i < n) dp[sccIdx[i]] = max(dp[sccIdx[i]], d[i]);

        for(int nxt : g[i]) {
            if(sccIdx[i] == sccIdx[nxt]) continue;
            in[sccIdx[nxt]]++;
            rev[sccIdx[nxt]].push_back(sccIdx[i]);
        }
    }

    queue<int> q;
    for(int i = 0; i < sccs.size(); ++i) {
        if(in[i] == 0) q.push(i);
    }
    vector<int> order;
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        order.push_back(cur);

        for(int v : sccs[cur]) {
            for(int nx : g[v]) {
                int nxt = sccIdx[nx];
                if(nxt == cur) continue;
                dp[nxt] = max(dp[nxt], dp[cur]);
                in[nxt]--;
                if(in[nxt] == 0) q.push(nxt);
            }
        }
    }

    for(int cur : order) {
        if(sccs[cur].size() > 1) continue;
        int v = sccs[cur][0];
        if(v < n && (v < l[v] || r[v] < v)) {
            dp[cur] = 0;
            for(int pre : rev[cur]) {
                dp[cur] = max(dp[cur], dp[pre]);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << dp[sccIdx[i]] << " ";
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
