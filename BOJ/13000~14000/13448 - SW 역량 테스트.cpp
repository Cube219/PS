#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, t;
ll dp[2][100011];

struct Node
{
    ll m;
    ll p;
    ll r;
};
Node d[51];
ll res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t;
    for(int i = 0; i < n; i++) {
        cin >> d[i].m;
    }
    for(int i = 0; i < n; i++) {
        cin >> d[i].p;
    }
    for(int i = 0; i < n; i++) {
        cin >> d[i].r;
    }
    sort(d, d + n, [](const Node& l, const Node& r) { return (l.r*r.p) < (r.r*l.p); });

    for(int i = 0; i < n; i++) {
        int cur = i % 2;
        int before = 1 - cur;
        for(int j = 0; j < d[i].r; j++) {
            dp[cur][j] = dp[before][j];
        }
        for(ll j = d[i].r; j <= t; j++) {
            dp[cur][j] = dp[before][j];

            ll score = d[i].m - d[i].p * j;
            if(score <= 0) {
                continue;
            }

            if(dp[cur][j] < dp[before][j - d[i].r] + score) {
                dp[cur][j] = dp[before][j - d[i].r] + score;
                if(dp[cur][j] > res) res = dp[cur][j];
            }
        }
    }

    cout << res;

    return 0;
}
