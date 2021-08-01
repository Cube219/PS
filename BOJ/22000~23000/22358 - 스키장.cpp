#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int s, e;
    ll t;
};

int n, m, k, s, t;
ll dp[100001];
Node d[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k >> s >> t;
    s--; t--;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        d[i] = { a, b, c };
    }
    sort(d, d + m, [](const Node& l, const Node& r) {
        return l.s < r.s;
    });

    for(int i = 0; i < n; ++i) {
        dp[i] = -1;
    }
    dp[s] = 0;
    for(int i = 0; i < m; ++i) {
        if(dp[d[i].s] == -1) continue;
        dp[d[i].e] = max(dp[d[i].e], dp[d[i].s] + d[i].t);
    }

    for(int cnt = 0; cnt < k; ++cnt) {
        ll cur = dp[n - 1];
        for(int i = 0; i < m; ++i) {
            if(dp[d[i].e] == -1) continue;
            dp[d[i].s] = max(dp[d[i].s], dp[d[i].e]);
        }

        for(int i = 0; i < m; ++i) {
            if(dp[d[i].s] == -1) continue;
            dp[d[i].e] = max(dp[d[i].e], dp[d[i].s] + d[i].t);
        }
    }

    cout << dp[t];

    return 0;
}
