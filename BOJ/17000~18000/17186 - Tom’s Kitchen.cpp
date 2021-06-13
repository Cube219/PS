#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n, m, k;
int a[301], b[301];
int dp[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    for(int i = 1; i <= 100000; ++i) {
        dp[i] = -INF;
    }
    int bsum = 0;
    for(int i = 0; i < m; ++i) {
        bsum += b[i];
        for(int j = 100000; j >= b[i]; --j) {
            dp[j] = max(dp[j], dp[j - b[i]] + min(n, b[i]));
        }
    }

    int sum = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] < k) {
            cout << "Impossible";
            return 0;
        }
        sum += a[i];
    }
    for(int i = sum; i <= 100000; ++i) {
        if(dp[i] >= n * k) {
            cout << i - sum;
            return 0;
        }
    }
    cout << "Impossible";

    return 0;
}
