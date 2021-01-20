#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, e[100001];
vector<pair<int, int>> g[100001];
pair<int, int> d[100001][20];

bool isVisited[100001];
void dfs(int node)
{
    isVisited[node] = true;

    for(auto& n : g[node]) {
        int next = n.first;
        int cost = n.second;
        if(isVisited[next] == true) continue;

        d[next][0] = { node, cost };
        dfs(next);
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> e[i];
    }
    for(int i = 0; i < n - 1; i++) {
        int a, b, cost;
        cin >> a >> b >> cost;
        g[a].push_back({ b, cost });
        g[b].push_back({ a, cost });
    }
    d[1][0] = { 1, 0 };
    dfs(1);

    for(int i = 1; i < 20; i++) {
        for(int j = 1; j <= n; j++) {
            pair<int, int> v = { j, 0 };
            int cost = 0;
            v = d[v.first][i - 1];
            cost += v.second;
            v = d[v.first][i - 1];
            cost += v.second;
            d[j][i] = { v.first, cost };
        }
    }

    for(int i = 0; i < n; i++) {
        int cCost = e[i];
        int current = i + 1;
        for(int j = 19; j >= 0; j--) {
            if(d[current][j].second <= cCost) {
                cCost -= d[current][j].second;
                current = d[current][j].first;
            }
        }
        cout << current << "\n";
    }

    return 0;
}
