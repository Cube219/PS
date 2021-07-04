#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 98765432;

int n;
char str[402];
vector<vector<vector<int>>> dp[3];
vector<int> r, g, y;
int rn, gn, yn;
vector<vector<int>> rshift, gshift, yshift;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;
    for(int i = 0; i < n; ++i) {
        if(str[i] == 'R') {
            r.push_back(i);
        } else if(str[i] == 'G') {
            g.push_back(i);
        } else {
            y.push_back(i);
        }
    }
    rn = r.size(); gn = g.size(); yn = y.size();
    for(int i = 0; i < 3; ++i) {
        dp[i].resize(rn + 1);
        for(auto& dpr: dp[i]) {
            dpr.resize(gn + 1);
            for(auto& dpg : dpr) {
                dpg.resize(yn + 1, INF);
            }
        }
    }
    dp[0][0][0][0] = 0;
    dp[1][0][0][0] = 0;
    dp[2][0][0][0] = 0;
    auto shiftinit = [](vector<vector<int>>& shift, vector<int>& color, int colorn) {
        shift.resize(colorn + 1);
        shift[0].resize(n);
        for(int i = 1; i <= colorn; ++i) {
            shift[i] = shift[i - 1];
            for(int j = 0; j <= color[i - 1]; ++j) {
                shift[i][j]++;
            }
        }
    };
    shiftinit(rshift, r, rn);
    shiftinit(gshift, g, gn);
    shiftinit(yshift, y, yn);

    for(int i = 0; i <= rn; ++i) {
        for(int j = 0; j <= gn; ++j) {
            for(int k = 0; k <= yn; ++k) {
                int idx = i + j + k - 1;
                // use r
                if(i > 0) {
                    int pos = r[i - 1];
                    int mv = pos - idx + rshift[i - 1][pos] + gshift[j][pos] + yshift[k][pos];
                    if(mv < 0) {
                        mv = mv;
                    }
                    dp[0][i][j][k] = min(dp[1][i - 1][j][k], dp[2][i - 1][j][k]);
                    dp[0][i][j][k] += mv;
                }
                // use g
                if(j > 0) {
                    int pos = g[j - 1];
                    int mv = pos - idx + rshift[i][pos] + gshift[j - 1][pos] + yshift[k][pos];
                    if(mv < 0) {
                        mv = mv;
                    }
                    dp[1][i][j][k] = min(dp[0][i][j - 1][k], dp[2][i][j - 1][k]);
                    dp[1][i][j][k] += mv;
                }
                // use y
                if(k > 0) {
                    int pos = y[k - 1];
                    int mv = pos - idx + rshift[i][pos] + gshift[j][pos] + yshift[k - 1][pos];
                    if(mv < 0) {
                        mv = mv;
                    }
                    dp[2][i][j][k] = min(dp[0][i][j][k - 1], dp[1][i][j][k - 1]);
                    dp[2][i][j][k] += mv;
                }
            }
        }
    }

    int res = dp[0][rn][gn][yn];
    res = min(res, dp[1][rn][gn][yn]);
    res = min(res, dp[2][rn][gn][yn]);
    if(res >= INF) res = -1;

    cout << res;

    return 0;
}
