#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
vector<pair<int, int>> g[100001];
int mins[100001][21], maxs[100001][21], parent[100001][21];
int depth[100001];

bool visit[100001];

void dfs(int node, int dep)
{
    visit[node] = true;
    depth[node] = dep;

    for(auto& nx : g[node]) {
        int next = nx.first;
        int cost = nx.second;

        if(visit[next] == true) continue;

        mins[next][0] = cost;
        maxs[next][0] = cost;
        parent[next][0] = node;

        dfs(next, dep + 1);
    }
}

void query(int a, int b)
{
    int minv = 9999999, maxv = -1;

    int adep = depth[a];
    int bdep = depth[b];
    if(adep > bdep) {
        swap(adep, bdep);
        swap(a, b);
    }

    int gap = bdep - adep;
    int idx = 0;
    while(gap > 0) {
        if(gap % 2 == 1) {
            minv = min(minv, mins[b][idx]);
            maxv = max(maxv, maxs[b][idx]);
            b = parent[b][idx];
        }
        idx++;
        gap /= 2;
    }

    if(a != b) {
        for(int i = 20; i >= 0; --i) {
            if(parent[a][i] != 0 && parent[a][i] != parent[b][i]) {
                minv = min(minv, mins[a][i]);
                minv = min(minv, mins[b][i]);
                maxv = max(maxv, maxs[a][i]);
                maxv = max(maxv, maxs[b][i]);
                a = parent[a][i];
                b = parent[b][i];
            }
        }
        minv = min(minv, mins[a][0]);
        minv = min(minv, mins[b][0]);
        maxv = max(maxv, maxs[a][0]);
        maxv = max(maxv, maxs[b][0]);
    }

    cout << minv << " " << maxv << "\n";
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    dfs(1, 0);

    for(int i = 1; i <= 20; ++i) {
        for(int j = 1; j <= n; ++j) {
            int p = parent[j][i - 1];
            parent[j][i] = parent[p][i - 1];
            mins[j][i] = min(mins[j][i - 1], mins[p][i - 1]);
            maxs[j][i] = max(maxs[j][i - 1], maxs[p][i - 1]);
        }
    }

    cin >> k;
    for(int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        query(a, b);
    }

    return 0;
}
