#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
ll d[500005];
ll dp[500005], idx[500005];
ll res = -1;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }
    sort(d, d + n);

    dp[3] = -2000000000;
    for(int i = 4; i < n - 2; i++) {
        dp[i] = -d[i] + d[i - 1] + d[i - 2] + d[i - 3] + d[i - 4];
        idx[i] = i;
        if(dp[i - 1] > dp[i]) {
            dp[i] = dp[i - 1];
            idx[i] = idx[i - 1];
        }
    }

    for(int i = 5; i < n - 1; i++) {
        for(int j = idx[i - 1]; j <= i - 1; j++) {
            ll p2 = d[i] + d[j];
            ll p3 = d[j - 1] + d[j - 2] + d[j - 3] + d[j - 4];
            if(p2 >= p3) continue;

            auto it = lower_bound(d + i + 1, d + n, p2);

            if(it != d + i + 1) {
                it--;
                ll p1 = *it;
                if(p1 + p2 + p3 > res) res = p1 + p2 + p3;
            }
        }
    }

    cout << res;

    return 0;
}
