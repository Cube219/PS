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
    ll r;
    cin >> n >> r;
    vector<vector<vector<int>>> d(10, vector<vector<int>>(n, vector<int>(n)));
    for(auto& v : d[0])
        for(auto& v2 : v) cin >> v2;

    for(int k = 1; k < 10; ++k) {
        int sz = 1 << k;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                int v = d[k - 1][i][j];
                if(i + sz / 2 < n) v = max(v, d[k - 1][i + sz / 2][j]);
                if(j + sz / 2 < n) v = max(v, d[k - 1][i][j + sz / 2]);
                if(i + sz / 2 < n && j + sz / 2 < n)
                    v = max(v, d[k - 1][i + sz / 2][j + sz / 2]);

                d[k][i][j] = v;
            }
        }
    }

    auto ck = [&](int sz) {
        ll sum = 0;
        int k = 0;
        while((1 << (k + 1) <= sz)) k++;
        int kk = 1 << k;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                int v = d[k][i][j];
                if(i + sz - kk < n) v = max(v, d[k][i + sz - kk][j]);
                if(j + sz - kk < n) v = max(v, d[k][i][j + sz - kk]);
                if(i + sz - kk < n && j + sz - kk < n)
                    v = max(v, d[k][i + sz - kk][j + sz - kk]);

                sum += v;
            }
        }
        return sum >= r;
    };

    int lo = 0, hi = n + 1;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if(ck(mid)) hi = mid;
        else
            lo = mid;
    }
    
    if(hi == n + 1) hi = -1;
    cout << hi;
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
