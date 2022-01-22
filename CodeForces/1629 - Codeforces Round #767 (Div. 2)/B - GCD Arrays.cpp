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
    ll l, r, k;
    cin >> l >> r >> k;

    if(k == 0) {
        if(l == r && r > 1) cout << "YES\n";
        else cout << "NO\n";
        return;
    }

    ll odd = (r + 1) / 2 - (l / 2);
    ll even = r / 2 - (l - 1) / 2;

    bool res = true;
    if(odd > k) res = false;

    if(res) cout << "YES\n";
    else cout << "NO\n";
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
