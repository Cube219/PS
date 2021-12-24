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
    ll l, r;
    cin >> l >> r;
    l--;
    ll res = LNF;
    ll tmp = 2;
    auto getnum = [&](ll v) {
        ll bnum = v / tmp;
        ll b = v % tmp;
        b -= tmp / 2;

        ll num = bnum * tmp / 2;
        if(b >= 0) num += b + 1;

        return num;
    };
    for(int i = 1; i <= 32; ++i) {
        ll rnum = getnum(r);
        ll lnum = getnum(l);

        res = min(res, r - l + 1 - (rnum - lnum));

        tmp *= 2;
    }

    cout << res - 1 << "\n";
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
