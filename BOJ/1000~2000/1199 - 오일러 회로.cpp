#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Edge
{
    int nxt, revidx;
    int use;
};

int n;
vector<Edge> g[1001];
vector<int> path;
bool comp[1001];
int cidx[1001];

void addEdge(int u, int v, int cost)
{
    Edge e1 = { v, -1, cost };
    Edge e2 = { u, -1, cost };
    e1.revidx = g[v].size();
    e2.revidx = g[u].size();
    g[u].push_back(e1);
    g[v].push_back(e2);
}

void dfs(int cur)
{
    comp[cur] = true;
    int& i = cidx[cur];
    for(; i < g[cur].size();) {
        Edge& e = g[cur][i];
        if(e.use == 0) {
            i++;
            continue;
        }

        e.use--;
        g[e.nxt][e.revidx].use--;
        dfs(e.nxt);
    }
    path.push_back(cur);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            int v;
            cin >> v;
            if(i >= j) continue;
            if(v > 0) addEdge(i, j, v);
        }
    }

    for(int i = 0; i < n; ++i) {
        int sum = 0;
        for(auto& e : g[i]) {
            sum += e.use;
        }
        if((sum & 1) == 1) {
            cout << "-1";
            return 0;
        }
    }

    for(int i = 0; i < n; ++i) {
        if(comp[i] == false) {
            dfs(i);
        }
    }

    for(int i = 0; i < path.size(); ++i) {
        cout << path[i] + 1 << " ";
    }

    return 0;
}
