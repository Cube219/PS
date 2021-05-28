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
constexpr ll INF = 999999999999999;

int n, d;
ll k[100001];
deque<int> dq;
ll dp[100001];
ll res = -INF;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> d;
    for(int i = 0; i < n; ++i) {
        cin >> k[i];
    }

    dp[0] = k[0];
    dq.push_back(0);
    res = k[0];
    for(int i = 1; i < n; ++i) {
        while(dq.size() > 0 && dq.front() < i - d) dq.pop_front();
        dp[i] = max(k[i], dp[dq.front()] + k[i]);
        while(dq.size() > 0) {
            if(dp[dq.back()] > dp[i]) break;
            dq.pop_back();
        }
        dq.push_back(i);

        res = max(res, dp[i]);
    }

    cout << res;

    return 0;
}
