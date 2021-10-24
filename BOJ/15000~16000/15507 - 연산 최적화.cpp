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
constexpr int INF = 987654321;

struct ZFunc
{
    vector<int> z;

    void build(const string& s)
    {
        int n = (int)s.size();
        z.clear();
        z.resize(s.size());
        for(int i = 1, l = 0, r = 0; i < n; ++i) {
            if(i <= r) z[i] = min(r - i + 1, z[i - l]);
            while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if(i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }
};

int n;
string str;
ZFunc zf;
int dp[31][1000007];

int get(int k, int b)
{
    for(int i = 0; i <= k; ++i) {
        for(int j = 1; j <= b; ++j) {
            dp[i][j] = INF;
        }
    }
    for(int i = 0; i <= k; ++i) {
        dp[i][0] = i;
    }

    for(int j = 1; j <= b; ++j) {
        if(str[j - 1] != str[j + b - 1]) break;
        dp[0][j] = dp[0][j - 1] + 1;
    }
    int ii = 1;
    for(int i = 1; i <= k; ++i) {
        for(int j = 1; j * 2 <= b; ++j) {
            // [i-1][j] -> [i][j*2]
            int nj = ii * b + j;
            if(zf.z[j] >= j && zf.z[nj] >= nj) {
                dp[i][j * 2] = dp[i - 1][j] + 1;
            }
        }

        ii *= 2;
        for(int j = 1; j <= b; ++j) {
            int nj = ii * b + j;
            if(str[j - 1] == str[nj - 1]) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
        }
    }

    return dp[k][b];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;

    zf.build(str);

    int res = INF;
    int kk = 1;
    for(int i = 0; i <= 30; ++i, kk *= 2) {
        if(n / (kk + 1) == 0) break;
        if(n % (kk + 1) != 0) continue;

        res = min(res, get(i, n / (kk + 1)));
    }

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
