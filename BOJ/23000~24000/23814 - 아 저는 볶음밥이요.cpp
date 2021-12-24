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

void solve()
{
    ll d, a, b, k;
    cin >> d >> a >> b >> k;

    ll ra = d - a % d;
    ll rb = d - b % d;
    if(ra == d) ra = 0;
    if(rb == d) rb = 0;
    if(ra > rb) swap(ra, rb);

    ll rk = k % d;
    if(ra <= rk) {
        rk -= ra;
        ra = d;
    }
    if(rb <= rk) {
        rk -= rb;
        rb = d;
    }

    if(ra + rb <= d + rk) {
        rk -= ra + rb;
        if(k / d * d + rk < 0) {
            rk += ra + rb;
        }
    }

    cout << k / d * d + rk;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
