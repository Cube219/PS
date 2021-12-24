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
    ll n;
    cin >> n;
    ll tmp = n;
    int sz = 0;
    while(tmp > 0) {
        sz++;
        tmp /= 10;
    }
    ll offset = 1;
    for(int i = 0; i < sz - 1; ++i) {
        offset *= 10;
    }

    ll res = 0;
    for(int i = 0; i < sz; ++i) {
        res += n;
        ll t = n % 10;
        n /= 10;
        n += t * offset;
    }

    cout << res;
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
