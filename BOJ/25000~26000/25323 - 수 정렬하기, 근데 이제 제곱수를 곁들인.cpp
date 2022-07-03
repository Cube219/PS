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
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    auto d2 = d;
    sort(d2.begin(), d2.end());

    auto isSq = [&](ll x) {
        ll lo = 0, hi = 10e9;
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(mid * mid >= x) hi = mid;
            else lo = mid;
        }

        return hi * hi == x;
    };

    for(int i = 0; i < n; ++i) {
        ll g = gcd(d[i], d2[i]);
        if(!isSq(d[i] / g) || !isSq(d2[i] / g)) {
            cout << "NO";
            return;
        }
    }
    cout << "YES";
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
