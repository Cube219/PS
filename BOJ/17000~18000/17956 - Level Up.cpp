#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

struct Node
{
    int e1, t1, e2, t2;
};

int n, s1, s2;
Node d[501];
ll dp[501][501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> s1 >> s2;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].e1 >> d[i].t1 >> d[i].e2 >> d[i].t2;
    }

    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.e1 < r.e1;
    });

    for(int i = 0; i <= s1; ++i) {
        for(int j = 0; j <= s2; ++j) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;

    for(auto& cur : d){
        for(int i = s1; i >= 0; --i) {
            for(int j = s2; j >= 0; --j) {
                if(dp[i][j] == INF) continue;
                int ni, nj;
                // level 1
                if(i < s1) {
                    ni = i + cur.e1;
                    nj = j;
                    if(ni > s1) {
                        nj += ni - s1;
                        ni = s1;
                        nj = min(nj, s2);
                    }
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + cur.t1);
                }

                // level 2
                ni = i;
                nj = j + cur.e2;
                nj = min(nj, s2);
                dp[ni][nj] = min(dp[ni][nj], dp[i][j] + cur.t2);
            }
        }
    }

    ll res = dp[s1][s2];
    if(res == INF) res = -1;

    cout << res;

    return 0;
}
