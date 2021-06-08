#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int n, k;
vector<int> g[51];
ll dp[51][51];
ll res;

void p(int cur, int par)
{
    dp[cur][1] = 1;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        p(nxt, cur);

        vector<int> tmp(n + 1, 0);

        for(int i = n; i >= 1; --i) {
            for(int j = n - i; j >= 1; --j) {
                tmp[j + i] += dp[cur][j] * dp[nxt][i];
                tmp[j + i] %= MOD;
            }
        }
        for(int i = 1; i <= n; ++i) {
            dp[cur][i] += tmp[i];
            dp[cur][i] %= MOD;
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    p(0, -1);

    for(int i = 0; i < n; ++i) {
        res += dp[i][k];
        res %= MOD;
    }

    cout << res;

    return 0;
}
