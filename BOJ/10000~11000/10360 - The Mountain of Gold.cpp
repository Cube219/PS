#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr ll INF = 9999999999;

int tNum;
int n, m;
vector<pair<int, ll>> g[1001];
ll d[1001];
bool isInCycle[1001];
bool res;
bool isVisited[1001];

void dfs(int n)
{
    isVisited[n] = true;
    if(n == 0) {
        res = true;
        return;
    }

    for(auto ne : g[n]) {
        int next = ne.first;
        if(isVisited[next] == false) {
            dfs(next);

            if(res == true) return;
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;

        for(int i = 0; i < n; i++) {
            g[i].clear();
            isInCycle[i] = false;
            d[i] = INF;
            isVisited[i] = false;
        }
        res = false;

        for(int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({ b, c });
        }

        d[0] = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                for(auto ne : g[j]) {
                    int next = ne.first;
                    ll cost = ne.second;

                    if(d[next] > d[j] + cost) {
                        d[next] = d[j] + cost;

                        if(i == n - 1) isInCycle[next] = true;
                    }
                }
            }
        }

        if(d[0] < 0) {
            res = true;
        } else {
            for(int i = 1; i < n; i++) {
                if(isInCycle[i] == true) {
                    dfs(i);

                    if(res == true) break;
                }
            }
        }

        if(res == true) cout << "Case #" << tt << ": possible\n";
        else cout << "Case #" << tt << ": not possible\n";
    }

    return 0;
}