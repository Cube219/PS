#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Range
{
    int l, r;
};

int tNum;
int n;
Range d[101];
int dp[115][115];

int canwin(int l, int r)
{
    if(l >= r) return 0;
    if(dp[l][r] != -1) return dp[l][r];

    vector<bool> grundy(101, false);
    for(int i = 0; i < n; ++i) {
        if(l <= d[i].l && d[i].r <= r) {
            int g = canwin(l, d[i].l) ^ canwin(d[i].r, r);
            grundy[g] = true;
        }
    }
    for(int i = 0; i < 101; ++i) {
        if(grundy[i] == false) {
            dp[l][r] = i;
            break;
        }
    }

    return dp[l][r];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;

        for(int i = 0; i <= 104; ++i) {
            for(int j = 0; j <= 104; ++j) {
                dp[i][j] = -1;
            }
        }

        for(int i = 0; i < n; ++i) {
            cin >> d[i].l >> d[i].r;
        }
        int res = canwin(0, 104);
        if(res > 0) cout << "Alice\n";
        else cout << "Bob\n";
    }

    return 0;
}
