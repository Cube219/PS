#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

int n;
int u[200001], z[200001];
vector<int> r[200001];
ll dp[200001];

bool visit[200001];

ll dfs(int cur)
{
    if(dp[cur] != INF) return dp[cur];

    dp[cur] = z[cur];
    visit[cur] = true;

    ll res = u[cur];
    int nxt = -1, nxtCnt = 0;
    for(int i = 0; i < r[cur].size(); ++i) {
        if(nxt != r[cur][i]) {
            if(nxt != -1) {
                if(visit[nxt] == true) {
                    res = INF;
                    break;
                }
                ll tmp = dfs(nxt) * nxtCnt;
                res += tmp;
            }
            nxt = r[cur][i];
            nxtCnt = 0;
        }
        nxtCnt++;
    }
    if(nxt != -1) {
        if(visit[nxt] == true) {
            res = INF;
        } else {
            ll tmp = dfs(nxt) * nxtCnt;
            res += tmp;
        }
    }

    dp[cur] = min(dp[cur], res);

    visit[cur] = false;

    return dp[cur];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> u[i] >> z[i] >> num;
        r[i].resize(num);
        for(int j = 0; j < num; ++j) {
            cin >> r[i][j];
            r[i][j]--;
        }
        sort(r[i].begin(), r[i].end());
    }


    for(int i = 0; i < n; ++i) {
        dp[i] = INF;
    }

    dfs(0);
    cout << dp[0];

    return 0;
}
