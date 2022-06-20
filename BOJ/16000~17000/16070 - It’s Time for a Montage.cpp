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
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;

    int cur = 0, res = INF;
    for(int i = 0; i < n; ++i) {
        if(a[i] + cur > b[i]) {
            res = min(res, cur);
            break;
        }

        int v = b[i] - a[i] - cur;
        cur += v;
        res = min(res, cur + 1);
    }
    res = min(res, cur);

    cout << res;
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
