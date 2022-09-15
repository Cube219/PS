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
    vector<ll> t;
    Fenwick(int _n) : n(_n + 1), t(_n + 1, 0) {}

    void update(int pos, ll dv)
    {
        for(pos++; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    ll query(int pos)
    {
        ll res = 0;
        for(pos++; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    struct Node { int l, r, v; };
    vector<Node> d(n);
    vector<int> rr;
    for(auto& v : d) {
        cin >> v.l >> v.r >> v.v;
        rr.push_back(v.r);
    }
    sort(rr.begin(), rr.end());
    rr.erase(unique(rr.begin(), rr.end()), rr.end());

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        if(l.l == r.l) return l.r > r.r;
        return l.l < r.l;
    });

    Fenwick fw(rr.size());
    ll res = 0;
    for(int i = n - 1; i >= 0; --i) {
        auto [l, r, v] = d[i];
        int ridx = lower_bound(rr.begin(), rr.end(), r) - rr.begin();
        fw.update(ridx, v);
        res = max(res, fw.query(ridx));
    }

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
