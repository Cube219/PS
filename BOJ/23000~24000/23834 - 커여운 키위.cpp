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

struct Node
{
    int idx;
    ll v;
};

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; ++i) {
        cin >> b[i];
    }

    vector<ll> asum(n + 1), dp(n + 1);
    dp[0] = 0;
    asum[0] = 0;
    for(int i = 1; i <= n; ++i) {
        asum[i] = asum[i - 1] + a[i];
    }

    ll res = -INF;
    deque<Node> dq;
    dq.push_back({ 0, 0 });
    for(int i = 1; i <= n; ++i) {
        while(dq.size() > 0 && dq.front().idx < i - m) dq.pop_front();

        if(i < m) {
            dp[i] = asum[i - 1] - a[i];
        } else {
            dp[i] = dq.front().v + asum[i - 1] - a[i];
            res = max(res, dp[i - m] + asum[i] - asum[i - m] + b[i]);
        }

        while(dq.size() > 0 && dq.back().v <= dp[i] - asum[i]) dq.pop_back();
        dq.push_back({ i, dp[i] - asum[i] });
    }
    while(dq.size() > 0 && dq.front().idx < n - m + 1) dq.pop_front();
    res = max(res, dq.front().v + asum[n - 1] + a[n]);

    cout << res;

    return 0;
}
