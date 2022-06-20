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
    ll m;
    cin >> m;

    for(int n = 3; n <= 60; ++n) {
        ll cur = 0;
        for(int s = 1; s <= 100000000; ++s) {
            ll v = 1;
            for(int i = 0; i < n - 1; ++i) {
                v *= s;
                if(cur + v > m) break;
            }
            cur += v;
            if(cur == m) {
                cout << n << " " << s;
                return;
            } else if(cur > m) break;
        }
    }
    cout << "impossible";
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
