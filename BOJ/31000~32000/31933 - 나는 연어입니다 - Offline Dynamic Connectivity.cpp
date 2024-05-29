#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

struct DSU
{
    vector<int> par;
    vector<pair<int, int>> rec;

    DSU(int n)
        : par(n, -1)
    {
    }

    int find(int x)
    {
        while (par[x] >= 0) x = par[x];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (-par[a] < -par[b]) swap(a, b);
        rec.push_back({b, par[b]});
        par[a] += par[b];
        par[b] = a;
        return true;
    }

    int getTime()
    {
        return rec.size();
    }

    void rollback(int time)
    {
        for (; rec.size() != time; rec.pop_back()) {
            auto [b, sz] = rec.back();
            int a = par[b];
            par[a] -= sz;
            par[b] = sz;
        }
    }
};

void solve()
{
    struct Time
    {
        int t, revT;
        int op; // 0: 추가 / 1: 제거 / 2: 쿼리
        int idx;
    };
    vector<Time> list;

    int n, m;
    cin >> n >> m;
    struct Edge
    {
        int u, v;
    };
    vector<Edge> eg(m);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> eg[i].u >> eg[i].v >> l >> r;
        eg[i].u--;
        eg[i].v--;
        list.push_back({l, r + 1, 0, i});
        list.push_back({r + 1, l, 1, i});
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int v;
        cin >> v;
        list.push_back({v, v, 2, 0});
    }

    sort(list.begin(), list.end(), [](auto& l, auto& r) {
        if (l.t == r.t) return l.op < r.op;
        return l.t < r.t;
    });
    unordered_map<int, int> lIdx, rIdx;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].op == 0 && lIdx.find(list[i].t) == lIdx.end()) {
            lIdx.insert({list[i].t, i});
        } else if (list[i].op == 1 && rIdx.find(list[i].t) == rIdx.end()) {
            rIdx.insert({list[i].t, i});
        }
    }

    DSU dsu(n);
    int res = 0;
    auto dnc = [&](auto&& self, int l, int r) -> void {
        if (l == r) {
            if (list[l].op == 2) {
                if (dsu.find(0) == dsu.find(n - 1)) res++;
            }
            return;
        }

        int m = (l + r) / 2;

        // left
        int time = dsu.getTime();
        for (int i = m + 1; i <= r; ++i) {
            auto [u, v] = eg[list[i].idx];
            if (list[i].op == 1 && lIdx.find(list[i].revT)->second <= l) dsu.uni(u, v);
        }
        self(self, l, m);
        dsu.rollback(time);

        // right
        for (int i = l; i <= m; ++i) {
            auto [u, v] = eg[list[i].idx];
            if (list[i].op == 0 && r < rIdx.find(list[i].revT)->second) dsu.uni(u, v);
        }
        self(self, m + 1, r);
    };
    dnc(dnc, 0, list.size() - 1);

    cout << res;
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
