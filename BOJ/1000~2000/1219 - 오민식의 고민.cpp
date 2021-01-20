#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, st, ed;
ll w[101];
vector<pair<int, ll>> g[101];
ll d[101];
bool isInCycle[101];
bool isVisited[101];
bool isInf;

constexpr ll INF = 99999999999999;

void dfs(int node)
{
    isVisited[node] = true;
    if(node == ed) {
        isInf = true;
        return;
    }

    for(auto ne : g[node]) {
        int next = ne.first;
        if(isVisited[next] == true) continue;
        
        dfs(next);

        if(isInf == true) return;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> st >> ed >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, -c });
    }
    for(int i = 0; i < n; i++) {
        cin >> w[i];
    }

    for(int i = 0; i < n; i++) {
        for(auto& n : g[i]) {
            n.second += w[n.first];
        }
        d[i] = -INF;
    }
    d[st] = w[st];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(d[j] == -INF) continue;
            for(auto ne : g[j]) {
                int next = ne.first;
                ll cost = ne.second;

                if(d[next] < d[j] + cost) {
                    d[next] = d[j] + cost;

                    if(i == n - 1) isInCycle[j] = true;
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(isInCycle[i] == true) {
            dfs(i);

            if(isInf == true) break;
        }
    }

    if(isInf == true) cout << "Gee";
    else if(d[ed] == -INF) cout << "gg";
    else cout << d[ed];

    return 0;
}
