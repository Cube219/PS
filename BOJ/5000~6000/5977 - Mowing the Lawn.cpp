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
constexpr ll INF = 200000000000000;

int n, k;
ll d[100001], sum[100001], dp[100001], res;
deque<pair<ll, int>> dq;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sum[0] = d[0];
    for(int i = 1; i < n; ++i) {
        sum[i] = d[i] + sum[i - 1];
    }

    dq.push_back({ 0, -1 });
    for(int i = 0; i < n; ++i) {
        while(dq.empty() == false && dq.front().second < i - k - 1) {
            dq.pop_front();
        }

        ll v = 0;
        if(dq.empty() == false) v = dq.front().first;
        dp[i] = d[i] + v;

        v = dp[i];
        while(dq.empty() == false && dq.back().first >= v) {
            dq.pop_back();
        }
        dq.push_back({ v, i });
    }

    ll res = INF;
    for(int i = n - 1; i >= n - k - 1; --i) {
        res = min(res, dp[i]);
    }

    cout << sum[n - 1] - res;

    return 0;
}
