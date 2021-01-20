#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[101];
vector<int> res;
int d[101][101];
bool isVisited[101];
vector<int> nodes;

constexpr int INF = 987654321;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i != j) d[i][j] = INF;
        }
    }

    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        d[a][b] = d[b][a] = 1;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(isVisited[i] == true) continue;

        nodes.clear();
        for(int j = 1; j <= n; j++) {
            if(d[i][j] != INF) {
                nodes.push_back(j);
                isVisited[j] = true;
            }
        }

        int idx, mx = 987654321, cmx;
        for(auto node : nodes) {
            cmx = -1;
            for(int j = 1; j <= n; j++) {
                if(d[node][j] != INF && cmx < d[node][j]) {
                    cmx = d[node][j];
                }
            }
            if(mx > cmx) {
                mx = cmx;
                idx = node;
            }
        }
        res.push_back(idx);
    }

    sort(res.begin(), res.end());
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << "\n";
    }

    return 0;
}
