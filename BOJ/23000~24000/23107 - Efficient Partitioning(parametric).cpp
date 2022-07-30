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
    vector<ll> a(n), b(n), c(n);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;
    for(auto& v : c) cin >> v;

    auto ck = [&](ll k) -> bool {
        ll cur = b[0];
        for(int i = 0; i < n; ++i) {
            cur += a[i];
            if(cur + c[i] >= k) {
                if(i == n - 1) return true;
                cur = max(cur, b[i + 1]);
            }
        }
        return false;
    };

    ll mx = 1000000000ll * (n + 2);
    ll lo = -mx, hi = mx + 1;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(ck(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo;
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
