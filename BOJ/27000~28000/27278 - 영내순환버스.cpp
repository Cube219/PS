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
    vector<ll> t(n);
    for(auto& v : t) cin >> v;

    vector<ll> tSum(n);
    tSum[0] = 0;
    for(int i = 1; i < n; ++i) {
        tSum[i] = tSum[i - 1] + t[i - 1];
    }
    ll total = tSum[n - 1] + t[n - 1];

    ll res = 0;
    for(int i = 0; i < m; ++i) {
        int st, ed; ll c;
        cin >> st >> ed >> c;
        st--; ed--;

        ll cycle = (c - tSum[st] + total - 1) / total;
        if(st > ed) cycle++;
        res = max(res, cycle * total + tSum[ed]);
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
