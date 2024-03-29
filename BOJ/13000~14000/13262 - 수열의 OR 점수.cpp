#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
vector<ll> dp[2];
vector<int> a;
ll res;

void dnq(int s, int e, int minj, int maxj)
{
    if(s > e) return;

    int i = (s + e) / 2;
    int ed = min(i, maxj);
    ll mx = -1;
    int midj = ed;
    int cur = 0;
    for(int k = i; k > ed; k--) {
        cur |= a[k];
    }
    for(int j = ed; j >= minj; --j) {
        cur |= a[j];
        if(dp[1][j - 1] == -1) continue;
        ll v = dp[1][j - 1] + cur;
        if(mx < v) {
            mx = v;
            midj = j;
        }
    }
    dp[0][i] = mx;
    dnq(s, i - 1, minj, midj);
    dnq(i + 1, e, midj, maxj);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    a.resize(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    dp[0].resize(n + 1, -1);
    dp[1].resize(n + 1, -1);
    dp[1][0] = 0;

    for(int i = 0; i < k; ++i) {
        dnq(1, n, 1, n);
        swap(dp[0], dp[1]);
    }

    cout << dp[1][n];

    return 0;
}
