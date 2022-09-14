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
    ll m, n;
    cin >> m >> n;
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    ll remain = accumulate(d.begin(), d.end(), 0LL) - m;
    sort(d.begin(), d.end());

    ll res = 0;
    for(ll i = 0; i < n; ++i) {
        ll v = min(d[i], remain / (n - i));
        res += v * v;
        remain -= v;
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
