#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <unordered_map>
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

    DSU(int n) : par(n, -1)
    {}

    int find(int x)
    {
        while(par[x] >= 0) x = par[x];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;

        if(-par[a] < -par[b]) swap(a, b);
        rec.push_back({ b, par[b] });
        par[a] += par[b];
        par[b] = a;
        return true;
    }

    int getTime() { return rec.size(); }

    void rollback(int time)
    {
        for(; rec.size() != time; rec.pop_back()) {
            auto [b, sz] = rec.back();
            int a = par[b];
            par[a] -= sz;
            par[b] = sz;
        }
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    struct Query
    {
        int t, u, v;
    };
    vector<Query> ql(q);
    for(auto& q : ql) {
        cin >> q.t >> q.u >> q.v;
        q.u--; q.v--;
        if(q.u > q.v) swap(q.u, q.v);
    }

    unordered_map <ll, int> mp;
    vector<int> lr(q);
    for(int i = 0; i < q; ++i) {
        auto& [t, u, v] = ql[i];
        ll key = (ll)u * n + v;
        if(t == 1) {
            mp.insert({ key, i });
        } else if(t == 2) {
            auto it = mp.find(key);
            int st = it->second;
            lr[st] = i;
            lr[i] = st;

            mp.erase(it);
        }
    }
    for(auto [_, st] : mp) {
        lr[st] = q;
    }

    DSU dsu(n);
    auto dnc = [&](auto&& self, int l, int r) -> void {
        if(l == r) {
            if(ql[l].t == 3) {
                int res = (dsu.find(ql[l].u) == dsu.find(ql[l].v) ? 1 : 0);
                cout << res << "\n";
            }
            return;
        }
        int m = (l + r) / 2;

        // left
        int time = dsu.getTime();
        for(int i = m + 1; i <= r; ++i) {
            if(ql[i].t == 2 && lr[i] <= l) dsu.uni(ql[i].u, ql[i].v);
        }
        self(self, l, m);
        dsu.rollback(time);

        // right
        for(int i = l; i <= m; ++i) {
            if(ql[i].t == 1 && r < lr[i]) dsu.uni(ql[i].u, ql[i].v);
        }
        self(self, m + 1, r);
    };
    dnc(dnc, 0, q - 1);
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
