#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> d(n + 1, vector<ll>(m, 0LL));
    for (int i = 0; i < n; ++i) {
        for (auto& v2 : d[i]) cin >> v2;
    }

    int mm = m - k + 1;
    vector<vector<ll>> d2(n, vector<ll>(mm));
    for (int i = 0; i < n; ++i) {
        ll sum = 0;
        for (int j = 0; j < k - 1; ++j) {
            sum += d[i][j] + d[i + 1][j];
        }

        for (int j = 0; j < mm; ++j) {
            sum += d[i][j + k - 1] + d[i + 1][j + k - 1];
            d2[i][j] = sum;
            sum -= d[i][j] + d[i + 1][j];
        }
    }

    struct DPNode
    {
        ll v, lmx, rmx;
        bool operator<(const DPNode& rhs) const
        {
            return v < rhs.v;
        }
    };
    vector<DPNode> dp(mm), nxt(mm);
    for (int i = 0; i < mm; ++i) {
        dp[i].v = d2[0][i];
    }
    auto Update = [mm](vector<DPNode>& d) {
        d[0].lmx = d[0].v;
        for (int i = 1; i < mm; ++i) {
            d[i].lmx = max(d[i - 1].lmx, d[i].v);
        }
        d[mm - 1].rmx = d[mm - 1].v;
        for (int i = mm - 2; i >= 0; i--) {
            d[i].rmx = max(d[i + 1].rmx, d[i].v);
        }
    };
    Update(dp);

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < mm; ++j) {
            nxt[j].v = 0;
            if (j - k >= 0) nxt[j].v = max(nxt[j].v, dp[j - k].lmx + d2[i][j]);
            if (j + k < mm) nxt[j].v = max(nxt[j].v, dp[j + k].rmx + d2[i][j]);

            ll sum = 0;
            for (int jj = j; jj < j + k; ++jj) {
                sum += d[i][jj];
                if (jj - k + 1 >= 0)
                    nxt[j].v = max(nxt[j].v, dp[jj - k + 1].v + d2[i][j] - sum);
            }
            for (int jj = j; jj < j + k; ++jj) {
                sum -= d[i][jj];
                if (jj + 1 < mm)
                    nxt[j].v = max(nxt[j].v, dp[jj + 1].v + d2[i][j] - sum);
            }
        }

        Update(nxt);
        swap(dp, nxt);
    }

    cout << max_element(dp.begin(), dp.end())->v;
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
