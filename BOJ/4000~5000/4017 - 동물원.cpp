#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
int d[10001][1 << 5];
int dp[10001][1 << 5];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int v, num1, num2;
        cin >> v;
        v--;

        // pos
        int pmask = 0;
        cin >> num1 >> num2;
        for(int j = 0; j < num1; ++j) {
            int a;
            cin >> a;
            a -= v + 1;
            if(a < 0) a += n;
            pmask |= (1 << a);
        }

        // neg
        int nmask = 0;
        for(int j = 0; j < num2; ++j) {
            int a;
            cin >> a;
            a -= v + 1;
            if(a < 0) a += n;
            nmask |= (1 << a);
        }

        for(int j = 0; j < (1 << 5); ++j) {
            if((pmask & j) > 0 || (nmask & j) != nmask) {
                d[v][j]++;
            }
        }
    }

    int res = 0;
    for(int init = 0; init < 1 << 5; ++init) {
        for(int mask = 0; mask < 1 << 5; ++mask) {
            dp[0][mask] = 0;
        }
        dp[0][init] = d[0][init];
        for(int i = 1; i < n - 4; ++i) {
            for(int mask = 0; mask < 1 << 5; ++mask) {
                int bmask = (mask & 15) << 1;
                dp[i][mask] = max(dp[i - 1][bmask], dp[i - 1][bmask + 1]) + d[i][mask];
            }
        }
        int idx = n - 4;
        for(int i = 4; i >= 1; --i) {
            int initsz = 5 - i;
            int mm = init & ((1 << initsz) - 1);
            mm <<= i;
            for(int mask = 0; mask < 1 << i; ++mask) {
                int curm = mask | mm;
                int bmask = (curm & 15) << 1;
                dp[idx][curm] = max(dp[idx - 1][bmask], dp[idx - 1][bmask + 1]) + d[idx][curm];
            }
            idx++;
        }

        int mm = init & ((1 << 4) - 1);
        mm <<= 1;
        res = max(res, dp[n - 1][mm]);
        res = max(res, dp[n - 1][mm + 1]);
    }

    cout << res;

    return 0;
}
