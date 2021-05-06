#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

int n;
vector<int> g[200001];
ll d[200001];
ll dp[200001][2];
vector<bool> rec[200001][2];

ll p(int cur, int has)
{
    if(dp[cur][has] != -INF) return dp[cur][has];
    dp[cur][has] = 0;
    if(has == 1) {
        dp[cur][has] = d[cur];
        for(int nxt : g[cur]) {
            dp[cur][has] += p(nxt, false);
            rec[cur][has].push_back(false);
        }
    } else {
        for(int nxt : g[cur]) {
            ll a = p(nxt, false);
            ll b = p(nxt, true);
            if(a < b) {
                dp[cur][has] += b;
                rec[cur][has].push_back(true);
            } else {
                dp[cur][has] += a;
                rec[cur][has].push_back(false);
            }
        }
    }
    return dp[cur][has];
}
vector<int> r1, r2;
void dfs(int cur, int has, vector<int>& r)
{
    if(has == true) r.push_back(cur);
    for(int i = 0; i < g[cur].size(); ++i) {
        if(rec[cur][has][i] == 1) dfs(g[cur][i], true, r);
        else dfs(g[cur][i], false, r);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
        dp[i][0] = -INF;
        dp[i][1] = -INF;
    }
    for(int i = 2; i <= n; ++i) {
        int a;
        cin >> a;
        g[a].push_back(i);
    }
    p(1, 0);
    p(1, 1);
    dfs(1, false, r1);
    dfs(1, true, r2);
    cout << dp[1][1] << " " << dp[1][0] << "\n";
    for(int i = 0; i < r2.size(); ++i) {
        cout << r2[i] << " ";
    }
    cout << "-1\n";
    for(int i = 0; i < r1.size(); ++i) {
        cout << r1[i] << " ";
    }
    cout << "-1\n";

    return 0;
}
