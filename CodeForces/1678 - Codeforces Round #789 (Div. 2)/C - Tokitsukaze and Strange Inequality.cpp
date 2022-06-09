#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#ifndef CUBE_PS
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif


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

    void update(int pos, int dv)
    {
        pos++;
        for(; pos < n; pos += (pos & -pos)) t[pos] += dv;
    }

    int query(int pos)
    {
        pos++;
        int res = 0;
        for(; pos > 0; pos -= (pos & -pos)) res += t[pos];
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) {
        cin >> v;
        v--;
    }

    vector<Fenwick> sg(n, Fenwick(n));
    for(int i = 0; i < n; ++i) {
        for(int j = d[i] + 1; j < n; ++j) {
            sg[j].update(i, 1);
        }
    }

    ll res = 0;
    for(int i = 1; i < n; ++i) {
        for(int j = i + 1; j < n - 1; ++j) {
            ll v1 = sg[d[j]].query(i - 1);
            ll v2 = sg[d[i]].query(n - 1) - sg[d[i]].query(j);

            res += v1 * v2;
        }
    }

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
