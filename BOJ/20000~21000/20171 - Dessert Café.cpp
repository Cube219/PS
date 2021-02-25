#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
int d[100001];
vector<pair<int, int>> g[100001];
bool has[100001];
bool isc[100001];
int res;

constexpr int INF = 987654321;

int dfs(int cur, int prev)
{
    bool has = false;
    if(isc[cur] == true) {
        has = true;
    }
    int ret = 0;
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        int cost = nx.second;
        if(nxt == prev) continue;

        ret += dfs(nxt, cur);
    }

    if(ret > 0 || (ret == 0 && has == true)) {
        ret++;
    }

    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }
    for(int i = 0; i < k; ++i) {
        cin >> d[i];
        has[d[i]] = true;
        isc[d[i]] = true;
    }

    res = dfs(d[0], -1);

    cout << res;

    return 0;
}
