#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
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

    double res = 3.5;
    for(int i = 1; i < n; ++i) {
        double cnt = 0, sum = 0;
        for(int j = 1; j <= 6; ++j) {
            if(res < j) {
                cnt += 1;
                sum += j;
            }
        }
        res = sum / 6.0 + (6.0 - cnt) / 6.0 * res;
    }

    cout << fixed << setprecision(10) << res;
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
