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
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    int res = 0;
    for(int dx = -100; dx <= 100; ++dx) {
        vector<int> mx(101, 0);
        for(int i = 0; i < n; ++i) {
            int v = 1;
            if(0 <= d[i] - dx && d[i] - dx <= 100) {
                v += mx[d[i] - dx];
            }

            mx[d[i]] = max(mx[d[i]], v);
        }

        for(int i = 0; i < 101; ++i) {
            res = max(res, mx[i]);
        }
    }

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
