#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct Node
{
    int before, after;
    int idx;
};

int n, c;
Node d[501];
ll dp[501][501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].before >> d[i].after;
        d[i].idx = i;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return (l.before - l.after) > (r.before - r.after);
    });

    for(int i = 1; i <= n; ++i) {
        dp[0][i] = INF;
    }
    if(max(d[0].before, d[0].after) <= c) {
        dp[0][1] = d[0].after;
    }

    for(int i = 1; i < n; ++i) {
        for(int j = 0; j <= n; ++j) {
            dp[i][j] = dp[i - 1][j];
        }
        int cap = max(d[i].before, d[i].after);
        for(int j = 1; j <= n; ++j) {
            if(dp[i - 1][j - 1] + cap > c) continue;
            if(dp[i][j] > dp[i - 1][j - 1] + d[i].after) {
                dp[i][j] = dp[i - 1][j - 1] + d[i].after;
            }
        }
    }

    int k = 0;
    vector<int> res;
    for(int i = n; i >= 1; --i) {
        if(dp[n - 1][i] != INF) {
            k = i;
            break;
        }
    }
    for(int i = n - 1; i >= 1; --i) {
        if(dp[i][k] != dp[i - 1][k]) {
            res.push_back(d[i].idx);
            k--;
        }
        if(k == 0) break;
    }
    if(k == 1 && dp[0][k] != INF) res.push_back(d[0].idx);
    cout << res.size() << "\n";
    for(int i = res.size() - 1; i >= 0; --i) {
        cout << res[i] + 1 << " ";
    }

    return 0;
}
