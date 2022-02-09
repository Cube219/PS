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

struct Fenwick
{
    int n;
    vector<int> t;
    Fenwick(int _n) : n(_n + 1), t(_n + 1, 0) {}

    void update(int pos, int v)
    {
        pos++;
        for(; pos < n; pos += (pos & -pos)) t[pos] = max(t[pos], v);
    }
    void clear(int pos)
    {
        pos++;
        for(; pos < n; pos += (pos & -pos)) t[pos] = 0;
    }

    int query(int pos)
    {
        pos++;
        int res = 0;
        for(; pos > 0; pos -= (pos & -pos)) res = max(res, t[pos]);
        return res;
    }
};


void solve()
{
    struct Node
    {
        int a, b, c, sz;
    };

    int n, m;
    cin >> m >> n;
    vector<Node> d(n);
    vector<int> cc(1, 0);
    for(auto& v : d) cin >> v.a;
    for(auto& v : d) cin >> v.b;
    if(m == 3) {
        for(auto& v : d) {
            cin >> v.c;
            cc.push_back(v.c);
        }
        sort(cc.begin(), cc.end());
        cc.erase(unique(cc.begin(), cc.end()), cc.end());
        for(auto& v : d) {
            v.c = lower_bound(cc.begin(), cc.end(), v.c) - cc.begin();
        }
    } else {
        for(auto& v : d) v.c = 0;
    }
    for(auto& v : d) v.sz = 1;

    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        return l.a < r.a;
    });

    struct Node2
    {
        int b, c, idx, sz;
    };
    vector<Node2> ld, rd;
    Fenwick fw(cc.size());
    auto dnc = [&](auto&& self, int l, int r) -> void {
        if(l == r) return;
        int m = (l + r) / 2;
        self(self, l, m);

        ld.clear();
        for(int i = l; i <= m; ++i) {
            ld.push_back({ d[i].b, d[i].c, i, d[i].sz });
        }
        rd.clear();
        for(int i = m + 1; i <= r; ++i) {
            rd.push_back({ d[i].b, d[i].c, i, d[i].sz });
        }
        sort(ld.begin(), ld.end(), [](const Node2& l, const Node2& r) {
            return l.b > r.b;
        });
        sort(rd.begin(), rd.end(), [](const Node2& l, const Node2& r) {
            return l.b > r.b;
        });

        auto left = [&] {
            auto [b, c, idx, sz] = ld.back();
            fw.update(c, sz);
            ld.pop_back();
        };
        auto right = [&] {
            auto [b, c, idx, sz] = rd.back();
            d[idx].sz = max(sz, fw.query(c) + 1);
            rd.pop_back();
        };
        while(ld.size() > 0 && rd.size() > 0) {
            if(ld.back().b <= rd.back().b) left();
            else right();
        }
        while(ld.size() > 0) left();
        while(rd.size() > 0) right();

        for(int i = l; i <= m; ++i) {
            fw.clear(d[i].c);
        }

        self(self, m + 1, r);
    };
    dnc(dnc, 0, n - 1);

    int res = 0;
    for(auto& v : d) res = max(res, v.sz);
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
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
