#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> d(2000001, 0);
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        d[v]++;
    }

    ll res = 0;
    for(int i = 1; i <= 2000000; ++i) {
        int cnt = 0;
        for(int j = i; j <= 2000000; j += i) {
            cnt += d[j];
        }
        if(cnt > 1) res = max(res, (ll)cnt * i);
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
