#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>

using namespace std;

int n, k;
vector<pair<int, int>> g[1003];
int d[1003], remain[1003];
bool isVisited[1003];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &k);
    for(int i = 0; i < k; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        g[u].push_back({ v, t });
        g[v].push_back({ u, t });
    }

    for(int i = 1; i <= n + 1; i++) {
        d[i] = 987654321;
    }

    remain[0] = 100;
    pq.push({0, 0});
    while(pq.empty() == false) {
        auto p = pq.top();
        pq.pop();
        if(isVisited[p.second] == true) continue;

        int current = p.second;
        isVisited[current] = true;

        if(current == n + 1) break;

        for(auto child : g[current]) {
            int next = child.first;
            int cost = child.second;

            if(isVisited[next] == true) continue;

            if(remain[current] - cost >= 0 && d[next] > d[current] + cost) {
                d[next] = d[current] + cost;
                remain[next] = remain[current] - cost;

                pq.push({ d[next], next });
            }
            if(cost <= 100 && d[next] > d[current] + cost + 5) {
                d[next] = d[current] + cost + 5;
                remain[next] = 100 - cost;

                pq.push({ d[next], next });
            }
        }
    }

    printf("%d", d[n + 1]);

    return 0;
}
