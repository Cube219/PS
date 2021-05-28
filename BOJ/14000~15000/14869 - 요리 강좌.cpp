#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

int n, m, s, e, t;
int d[3001][6002], ban[3001];
ll sum[3001][6002];
deque<pair<int, ll>> dq[3001];
ll dp[3001][6002];
pair<ll, int> tmp[3001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> s >> e >> t;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> d[i][j];
            sum[i][j] = d[i][j];
            if(j > 0) sum[i][j] += sum[i][j - 1];
        }
        for(int j = m; j < m + s; ++j) {
            sum[i][j] = sum[i][j - 1];
        }
    }
    for(int i = 0; i < n; ++i) {
        cin >> ban[i];
        ban[i]--;
    }
    for(int j = 0; j < m + s; ++j) {
        int j0 = max(0, j - e);
        if(j - s >= 0) {
            for(int i = 0; i < n; ++i) {
                tmp[i] = { dp[i][j - s], i };
            }
            sort(tmp, tmp + n);
            for(int i = 0; i < n; ++i) {
                while(dq[i].size() > 0 && dq[i].front().first < j0) dq[i].pop_front();
                int k = 0;
                while(1) {
                    if(tmp[k].second == i || tmp[k].second == ban[i]) {
                        k++;
                        continue;
                    }
                    ll v = tmp[k].first - sum[i][j - s] + t;
                    while(dq[i].size() > 0 && dq[i].back().second >= v) {
                        dq[i].pop_back();
                    }
                    dq[i].push_back({ j - s, v });
                    break;
                }
            }
        }

        for(int i = 0; i < n; ++i) {
            dp[i][j] = INF;
            if(j >= s - 1 && j < e) dp[i][j] = sum[i][j];
            if(dq[i].size() > 0) {
                dp[i][j] = min(dp[i][j], sum[i][j] + dq[i].front().second);
            }
        }
    }
    ll res = INF;
    for(int i = 0; i < n; ++i) {
        for(int j = m - 1; j < m + s; ++j) {
            res = min(res, dp[i][j]);
        }
    }

    cout << res;

    return 0;
}
