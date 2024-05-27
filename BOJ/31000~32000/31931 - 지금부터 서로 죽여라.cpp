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
    ll h1, h2, a1, a2, d1, d2;
    cin >> h1 >> h2 >> a1 >> d1 >> a2 >> d2;

    int res = 0;
    if (a1 >= h2) {
        res = -1;
    } else {
        ll num1 = (h2 - 1) / a1;
        ll num2 = (h1 - 1) / a2;
        if (a1 < d2) {
            if (d1 >= a2) res = 0;
            else res = 1;
        } else if (a1 > d2) {
            if (d1 > a2) res = -1;
            else {
                if (num1 <= num2) res = -1;
                else {
                    if (d1 == a2) res = 0;
                    else res = 1;
                }
            }
        } else { // a1 == d2
            if (num1 <= num2) {
                res = 0;
            } else {
                if (d1 >= a2) res = 0;
                else res = 1;
            }
        }
    }

    if (res == -1) cout << "NARUTO\n";
    else if (res == 0) cout << "DRAW\n";
    else cout << "SASUKE\n";
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
    for (int tt = 1; tt <= tNum; tt++) {
        if (tt == 14) {
            int abc = 123;
        }
        solve();
    }

    return 0;
}