#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, k;
vector<pair<int, int>> g[1001];
ll dp[1001][1001];
int st, ed;
ll tax;

constexpr ll INF = 9999999999;

ll minV = INF;
int len;
vector<pair<ll, int>> r;

void p()
{
    for(int i = 1; i <= n; ++i) {
        dp[i][0] = INF;
    }
    dp[st][0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int cur = 1; cur <= n; ++cur) {
            dp[cur][i] = INF;
            for(auto& nx : g[cur]) {
                int prev = nx.first;
                ll cost = nx.second;
                if(dp[prev][i - 1] != INF && dp[cur][i] > dp[prev][i - 1] + cost) {
                    dp[cur][i] = dp[prev][i - 1] + cost;
                }
            }
            if(cur == ed) {
                if(minV > dp[cur][i]) {
                    minV = dp[cur][i];
                    len = i;
                }
            }
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    cin >> st >> ed;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    p();

    for(int i = 1; i <= len; i++) {
        if(dp[ed][i] != INF) {
            r.push_back({ dp[ed][i], i });
        }
    }
    int rSize = r.size();

    cout << r.back().first << "\n";
    for(int i = 0; i < k; ++i) {
        int p;
        cin >> p;
        tax += p;

        ll v = INF;
        int newRSize = rSize;
        for(int j = 0; j < rSize; ++j) {
            ll tmp = r[j].first + r[j].second * tax;
            if(v > tmp) {
                v = tmp;
                newRSize = j + 1;
            }
        }
        cout << v << "\n";
        rSize = newRSize;
    }

    return 0;
}
