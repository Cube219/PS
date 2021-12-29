#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    ll n, x;
    cin >> n;
    vector<ll> a(n);
    for(auto& v : a) cin >> v;
    cin >> x;

    for(auto& v : a) v -= x;

    int res = n;
    ll cur = -LNF;
    ll mn = LNF;
    for(int i = 0; i < n; ++i) {
        if(cur == -LNF) {
            cur = a[i];
        } else {
            cur = min(a[i] + a[i - 1], cur + a[i]);
            if(cur < 0) {
                cur = -LNF;
                res--;
            }
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
