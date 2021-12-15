#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        ll n, h;
        cin >> n >> h;
        vector<ll> a(n);
        for(auto& v : a) cin >> v;

        auto ck = [&](ll k) {
            ll res = 0;
            for(int i = 1; i < n; ++i) {
                res += min(a[i] - a[i - 1], k);
            }
            res += k;
            if(res >= h) return true;
            return false;
        };

        ll lo = 0, hi = 1000000000000000000;
        while(lo + 1 < hi) {
            ll mid = (lo + hi) / 2;
            if(ck(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }

        cout << hi << "\n";
    }

    return 0;
}
