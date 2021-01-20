#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n, m;
vector<pair<int, ll>> g[501];
queue<int> q;
bool isInQ[501];
ll dis[501];
constexpr ll INF = 9999999999;
int upNum[501];
bool hasCycle;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
    }

    for(int i = 1; i <= n; i++) {
        dis[i] = INF;
    }

    dis[1] = 0;
    q.push(1);
    isInQ[1] = true;
    while(q.empty() == false) {
        int cur = q.front();
        q.pop();

        isInQ[cur] = false;

        upNum[cur]++;
        if(upNum[cur] >= n) {
            hasCycle = true;
            break;
        }

        for(auto n : g[cur]) {
            int next = n.first;
            ll cost = n.second;

            if(dis[next] > dis[cur] + cost) {
                dis[next] = dis[cur] + cost;

                if(isInQ[next] == false) {

                    q.push(next);
                    isInQ[next] = true;
                }
            }
        }
    }

    if(hasCycle == true) {
        cout << "-1";
    } else {
        for(int i = 2; i <= n; i++) {
            if(dis[i] == INF) cout << "-1\n";
            else cout << dis[i] << "\n";
        }
    }

    return 0;
}
