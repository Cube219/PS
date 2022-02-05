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
    vector<vector<int>> dp(51, vector<int>(51, -1));
    dp[0][0] = 0;
    for(int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;

        for(int j = 51 - 1; j >= 0; --j) {
            if(j - a < 0) break;

            for(int k = 51 - 1; k >= 0; --k) {
                if(k - b < 0) break;

                if(dp[j - a][k - b] != -1) {
                    dp[j][k] = max(dp[j][k], dp[j - a][k - b] + w);
                }
            }
        }
    }

    vector<pair<int, int>> res(n);
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        res[i] = { dp[a][b], i };
        if(res[i].first == -1) res[i].first = 0;
    }
    sort(res.begin(), res.end());

    for(auto [w, idx] : res) {
        cout << idx + 1 << " " << w << "\n";
    }
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
