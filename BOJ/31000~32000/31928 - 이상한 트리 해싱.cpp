#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    ll h;
    cin >> h;

    int lgh = 0;
    while (h > 0 && h % 2 == 0) {
        h >>= 1;
        lgh++;
    }
    if (h != 1) {
        cout << "-1";
        return;
    }

    int lglgh = 0;
    while (lgh > 0 && lgh % 2 == 0) {
        lgh >>= 1;
        lglgh++;
    }
    if (lgh != 1) {
        cout << "-1";
        return;
    }
    if (lglgh < 2) {
        cout << "-1";
        return;
    }

    cout << lglgh + 1 << " " << lglgh + 1 << "\n";

    for (int i = 0; i < lglgh; ++i) {
        cout << "1 ";
    }
    cout << "\n";

    for (int i = 0; i < lglgh - 1; ++i) {
        cout << "1 ";
    }
    cout << "2";
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
