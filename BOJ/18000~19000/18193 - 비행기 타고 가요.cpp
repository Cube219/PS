#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
#include <queue>
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

    void query(int l, int r, vector<int>& res)
    {
        res.clear();
        l += n;
        r += n + 1;
        while(l < r) {
            if(l & 1) res.push_back(t[l++]);
            if(r & 1) res.push_back(t[--r]);
            l >>= 1;
            r >>= 1;
        }
    }
};

void solve()
{
    int n, m, st;
    cin >> n >> m >> st;
    st--;

    struct Nxt
    {
        int nxt;
        int v;
    };
    vector<vector<Nxt>> g(n * 4 + m * 2);
    SegTree stSeg(n), edSeg(n);
    int idx = 0;
    for(int i = 0; i < n; ++i) stSeg.t[n + i] = idx++;
    for(int i = n - 1; i > 0; --i) {
        stSeg.t[i] = idx++;
        int u = stSeg.t[i * 2], v = stSeg.t[i];
        g[u].push_back({ v, 0 });
        u = stSeg.t[i * 2 + 1];
        g[u].push_back({ v, 0 });
    }

    for(int i = 0; i < n; ++i) {
        edSeg.t[n + i] = idx++;
        g[idx - 1].push_back({ i, 0 });
    }
    for(int i = n - 1; i > 0; --i) {
        edSeg.t[i] = idx++;
        int u = edSeg.t[i], v = edSeg.t[i * 2];
        g[u].push_back({ v, 0 });
        v = edSeg.t[i * 2 + 1];
        g[u].push_back({ v, 0 });
    }
    vector<int> stList, edList;
    for(int i = 0; i < m; ++i) {
        int a, s1, s2, e1, e2;
        cin >> a >> s1 >> s2 >> e1 >> e2;
        s1--; s2--; e1--; e2--;

        stSeg.query(s1, s2, stList);
        edSeg.query(e1, e2, edList);

        for(int v : stList) {
            g[v].push_back({ idx, 0 });
        }
        for(int v : edList) {
            g[idx + 1].push_back({ v, 0 });
        }
        g[idx].push_back({ idx + 1, a });
        idx += 2;
    }

    vector<ll> d(idx, LNF);
    d[st] = 0;
    struct QNode
    {
        int cur;
        ll v;
        bool operator<(const QNode& rhs) const { return v > rhs.v; }
    };
    priority_queue<QNode> pq;
    pq.push({ st, 0 });
    while(!pq.empty()) {
        auto [cur, v] = pq.top(); pq.pop();

        if(d[cur] < v) continue;

        for(auto [nxt, cost] : g[cur]) {
            if(d[nxt] > d[cur] + cost) {
                d[nxt] = d[cur] + cost;
                pq.push({ nxt, d[nxt] });
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        if(d[i] == LNF) cout << "-1 ";
        else cout << d[i] << " ";
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
