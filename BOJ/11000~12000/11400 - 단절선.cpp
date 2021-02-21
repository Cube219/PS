#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int v, e;
vector<int> g[100001];
vector<pair<int, int>> res;

int d[100001], dNum = 1;
bool finish[100001];
vector<int> st;
int dfs(int cur, int prev)
{
    d[cur] = dNum++;

    int ret = d[cur];
    for(int nxt : g[cur]) {
        if(nxt == prev) continue;

        if(d[nxt] == 0) ret = min(ret, dfs(nxt, cur));
        else if(finish[nxt] == false) ret = min(ret, d[nxt]);
    }

    if(ret == d[cur] && prev != -1) {
        res.push_back({ cur, prev });
    }

    return ret;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;
    for(int i = 0; i < e; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int i = 1; i <= v; ++i) {
        if(finish[i] == false) dfs(i, -1);
    }

    for(int i = 0; i < res.size(); ++i) {
        if(res[i].first > res[i].second) {
            swap(res[i].first, res[i].second);
        }
    }
    sort(res.begin(), res.end());
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i].first << " " << res[i].second << "\n";
    }

    return 0;
}
