#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int tNum;
int n, m, w;
vector<pair<int, ll>> g[501];
queue<int> q;
ll d[501];
bool isVis[501], hasQ[501];
bool hasCycle;
int num[501];

constexpr ll INF = 9999999999;

void search(int st)
{
    for(int i = 1; i <= n; i++) {
        hasQ[i] = false;
        num[i] = 0;
    }

    d[st] = 0;
    q.push(st);
    hasQ[st] = true;
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();
        hasQ[cur] = false;

        num[cur]++;
        isVis[cur] = true;
        if(num[cur] > n) {
            hasCycle = true;
            break;
        }

        for(auto n : g[cur]) {
            int next = n.first;
            ll cost = n.second;
            
            if(d[next] > d[cur] + cost) {
                d[next] = d[cur] + cost;
                if(hasQ[next] == false) {
                    q.push(next);
                    hasQ[next] = true;
                }
            }
        }
    }

    while(q.empty() == false) q.pop();
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m >> w;

        for(int i = 1; i <= n; i++) {
            g[i].clear();
            d[i] = INF;
            isVis[i] = false;
        }
        hasCycle = false;

        for(int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({ b, c });
            g[b].push_back({ a, c });
        }
        for(int i = 0; i < w; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({ b, -c });
        }

        for(int i = 1; i <= n; i++) {
            if(isVis[i] == true) continue;
            search(i);
            if(hasCycle == true) break;
        }

        if(hasCycle == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
