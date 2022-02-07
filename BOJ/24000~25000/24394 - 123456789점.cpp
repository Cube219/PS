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
    ll n, s;
    cin >> n >> s;

    constexpr ll t9 = 1'000'000'000;

    auto ck = [&](ll gnum) {
        if(gnum > n * 2) return false;

        ll greatNum = gnum / 2;
        gnum = gnum & 1;
        ll news = t9 * (greatNum * 2 + gnum) / (n * 2);
        ll gap = s - news;
        if(greatNum < gap || gap < 0) {
            return false;
        }
        cout << greatNum * 2 + gnum << " " << gap << "\n";
        return true;
    };

    ll gnum = (s * n * 2) / t9;
    if(ck(gnum) == true) return;
    if(ck(gnum + 1) == true) return;
    cout << "-1\n";
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
