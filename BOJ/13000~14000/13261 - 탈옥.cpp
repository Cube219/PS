#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 640000000000000000;

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, g;
    cin >> n >> g;
    vector<int> c(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> c[i];
    }

    vector<ll> sum(n + 1);
    sum[0] = 0;
    for(int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + c[i];
    }

    vector<ll> dp[2];
    dp[0].resize(n + 1, INF);
    dp[1].resize(n + 1, INF);
    dp[0][0] = 0;
    dp[1][0] = 0;

    auto dnq = [&](auto&& self, int s, int e, int minj, int maxj) {
        if(s > e) return;

        int i = (s + e) / 2;

        int midj = minj;
        ll mn = INF;
        int ed = min(maxj, i);
        for(int j = minj; j <= ed; ++j) {
            ll v = dp[1][j] + (sum[i] - sum[j]) * (i - j);
            if(mn > v) {
                mn = v;
                midj = j;
            }
        }
        dp[0][i] = mn;
        self(self, s, i - 1, minj, midj);
        self(self, i + 1, e, midj, maxj);
    };
    for(int i = 0; i < g; ++i) {
        dnq(dnq, 1, n, 0, n);
        swap(dp[0], dp[1]);
        fill(dp[0].begin() + 1, dp[0].end(), INF);
    }

    cout << dp[1][n];

    return 0;
}
