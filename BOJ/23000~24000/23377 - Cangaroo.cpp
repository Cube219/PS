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
    int n, m;
    cin >> n >> m;
    vector<string> map(n);
    for(auto& v : map) cin >> v;

    vector<int> dp(1 << m, 0), ndp(1 << m, INF);

    for(int i = n - 2; i >= 0; i -= 2) {
        for(int j = 0; j < 1 << m; ++j) {
            ndp[j] = INF;
            int cnt = 0, last = 0;
            for(int k = 0; k < m; ++k) {
                if(j & (1 << k)) {
                    cnt++;
                    last++;
                } else {
                    if(last & 1) break;
                    last = 0;
                }
            }
            if(last & 1) continue;

            bool pos = true;
            for(int k = 0; k < m; ++k) {
                if(j & (1 << k)) continue;
                if(map[i][k] == '#' || map[i + 1][k] == '#') pos = false;
            }
            if(!pos) continue;

            for(int j2 = 0; j2 < 1 << m; ++j2) {
                if(dp[j2] == INF) continue;
                bool ck = true;
                for(int k = 0; k < m; ++k) {
                    if((j & (1 << k)) == 0) continue;
                    if((j2 & (1 << k)) == 0 && (j2 & (1 << (k + 1))) == 0) {
                        ck = false;
                        break;
                    }
                    k++;
                }
                if(!ck) continue;

                ndp[j] = min(ndp[j], dp[j2] + cnt / 2);
            }
        }
        swap(dp, ndp);
    }

    int res = INF;
    for(int i = 0; i < 1 << m; ++i) res = min(res, dp[i]);
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
