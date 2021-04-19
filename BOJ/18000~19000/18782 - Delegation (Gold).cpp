#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> g[100001];
bool res[100001];
vector<int> dp[100001];
int has[100001];

int dfs(int cur, int par, int k)
{
    for(int nxt : g[cur]) {
        if(nxt == par) continue;
        int v = dfs(nxt, cur, k) % k;
        if(v == -1) return -1;
        dp[cur].push_back(v);
    }
    int ret = 0;
    if(dp[cur].size() > 0) {
        int cnt = 0;
        int x = 0;
        for(int i = 0; i < dp[cur].size(); ++i) {
            int v = dp[cur][i];
            if(v == 0) continue;
            if(has[k - v] > 0) {
                cnt--;
                has[k - v]--;
                x ^= k - v;
            } else {
                cnt++;
                has[v]++;
                x ^= v;
            }
        }
        for(int i = 0; i < dp[cur].size(); ++i) {
            has[dp[cur][i]] = 0;
        }

        if(cnt > 1) return -1;
        ret = x;
    }
    return (ret + 1) % k;
}

void ck(int v)
{
    for(int i = 1; i <= n; ++i) {
        dp[i].clear();
    }
    int r = dfs(1, -1, v);
    if(r == 1) res[v] = true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int n1 = n - 1;
    for(int i = 1; i * i <= n1; ++i) {
        if(n1 % i != 0) continue;
        ck(i);
        if(i != n1 / i) ck(n1 / i);
    }

    res[1] = true;
    for(int i = 1; i <= n - 1; ++i) {
        if(res[i] == true) cout << "1";
        else cout << "0";
    }

    return 0;
}
