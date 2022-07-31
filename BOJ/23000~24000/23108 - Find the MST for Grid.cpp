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
    int n, m;
    cin >> n >> m;
    vector<ll> a(n - 1), b(m), c(n), d(m - 1);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;
    for(auto& v : c) cin >> v;
    for(auto& v : d) cin >> v;

    ll res = 0;
    for(int i = 0; i < m - 1; ++i) {
        res += c[0] + d[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        res += a[i] + b[0];
    }

    struct Node
    {
        ll b, d, bd;
        bool operator<(const Node& rhs) const
        {
            return bd < rhs.bd;
        }
    };
    vector<Node> bd(m - 1);
    for(int i = 0; i < m - 1; ++i) {
        bd[i] = { b[i + 1], d[i], -b[i + 1] + d[i] };
    }
    sort(bd.begin(), bd.end());
    vector<ll> bsum(m - 1), dsum(m - 1);
    for(int i = 0; i < m - 1; ++i) {
        bsum[i] = bd[i].b;
        dsum[i] = bd[i].d;
        if(i > 0) {
            bsum[i] += bsum[i - 1];
            dsum[i] += dsum[i - 1];
        }
    }
    for(int i = 1; i < n; ++i) {
        Node bound = { 0, 0, a[i - 1] - c[i] };
        auto idx = lower_bound(bd.begin(), bd.end(), bound) - bd.begin();
        if(idx < m - 1) {
            res += a[i - 1] * (m - 1 - idx);
            res += bsum[m - 2];
            if(idx > 0) res -= bsum[idx - 1];
        }

        if(idx > 0) {
            res += c[i] * idx;
            res += dsum[idx - 1];
        }
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
