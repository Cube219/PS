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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;

    int res = -INF;
    int mx = -INF;
    for(int i = 0; i < n; ++i) {
        int v = b[i] == 1 ? -a[i] : a[i];
        mx = max(mx + v, v);
        res = max(res, mx);
    }

    for(int i = 0; i < n; ++i) {
        if(b[i] == 1) res += a[i];
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
