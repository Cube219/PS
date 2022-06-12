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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    sort(a.begin(), a.end());
    vector<ll> sum(n);
    sum[0] = a[0];
    for(int i = 1; i < n; ++i) {
        sum[i] = sum[i - 1] + a[i];
    }

    for(int i = 0; i < q; ++i) {
        ll x;
        cin >> x;

        auto idx = lower_bound(a.begin(), a.end(), x) - a.begin();
        ll lsum = 0;
        if(idx > 0) lsum = sum[idx - 1];
        ll rsum = sum[n - 1];
        if(idx > 0) rsum -= sum[idx - 1];

        lsum = x * idx - lsum;
        rsum = rsum - x * (n - idx);

        cout << lsum + rsum << "\n";
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
