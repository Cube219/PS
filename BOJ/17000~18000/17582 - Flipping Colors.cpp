#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;
constexpr ll INF = 9999999999999999;

int n;
int adj[301][301];
int rnum;
ll curcost;
int rnode[301];
int rnodenum;

void press(int node)
{
    for(int i = 0; i < n; ++i) {
        if(i == node) continue;

        if(adj[node][i] < 0) {
            rnum++;
            if(rnode[i] == 0) rnodenum++;
            if(rnode[node] == 0) rnodenum++;
            rnode[i]++;
            rnode[node]++;
        } else {
            rnum--;
            if(rnode[i] == 1) rnodenum--;
            if(rnode[node] == 1) rnodenum--;
            rnode[i]--;
            rnode[node]--;
        }
        adj[node][i] = -adj[node][i];
        adj[i][node] = -adj[i][node];
        curcost += adj[node][i];
    }
}

int cnt = 0;
bool visit[301];

void dfs(int cur)
{
    cnt++;
    visit[cur] = true;
    for(int i = 0; i < n; ++i) {
        if(visit[i] == true || adj[cur][i] <= 0) continue;
        dfs(i);
    }
}

ll process()
{
    rnum = 0;
    rnodenum = 0;
    curcost = 0;
    for(int i = 0; i < n; ++i) {
        rnode[i] = 0;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(adj[i][j] < 0) continue;
            rnum++;
            curcost += adj[i][j];
            if(rnode[i] == 0) rnodenum++;
            if(rnode[j] == 0) rnodenum++;
            rnode[i]++;
            rnode[j]++;
        }
    }

    ll res = INF;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            if(adj[i][j] > 0) {
                press(j);
            }
        }
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            press(j);
            if(rnum == n - 1 && rnodenum == n && res > curcost) {
                for(int k = 0; k < n; ++k) {
                    visit[k] = false;
                }
                cnt = 0;
                dfs(i);
                if(cnt == n) res = curcost;
            }
            press(j);
        }
    }

    if(res == INF) res = -1;
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n;
        if(n == 0) break;
        for(int i = 0; i < n - 1; ++i) {
            for(int j = i + 1; j < n; ++j) {
                int v;
                cin >> v;
                adj[i][j] = v;
                adj[j][i] = v;
            }
        }
        cout << process() << "\n";
    }

    return 0;
}
