#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999;

int n, m;
string str;
int pl[30], mi[30];
ll dp[2002][2002];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> str;
    for(int i = 0; i < n; ++i) {
        char ch;
        int a, b;
        cin >> ch >> a >> b;
        pl[ch - 'a'] = min(a, b);
        mi[ch - 'a'] = b;
    }

    for(int len = 2; len <= m; ++len) {
        for(int i = 0; i < m - len + 1; ++i) {
            int l = i;
            int r = i + len - 1;

            dp[l][r] = dp[l + 1][r] + pl[str[l] - 'a'];
            dp[l][r] = min(dp[l][r], dp[l][r - 1] + pl[str[r] - 'a']);
            if(str[l] == str[r]) {
                dp[l][r] = min(dp[l][r], dp[l + 1][r - 1]);
            }
        }
    }
    cout << dp[0][m - 1];

    return 0;
}
