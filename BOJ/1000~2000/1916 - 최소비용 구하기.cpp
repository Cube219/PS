#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int n, m, s, e;
vector<pair<int, int>> g[1001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[1001];
bool isVisited[1001];

int main(void)
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g[a].push_back({ b, c });
    }
    scanf("%d %d", &s, &e);

    for(int i = 1; i <= n; i++) {
        d[i] = 2147483647;
        isVisited[i] = false;
    }

    d[s] = 0;
    pq.push({ 0, s });
    while(pq.empty() == false) {
        int current = s;
        while(true) {
            current = pq.top().second;
            pq.pop();
            if(isVisited[current] == false || pq.empty()) break;
        }
        if(isVisited[current] == true) break;

        isVisited[current] = true;
        for(auto t : g[current]) {
            int next = t.first;
            int cost = t.second;
            if(isVisited[next] == true) continue;

            if(d[next] > d[current] + cost) {
                d[next] = d[current] + cost;
                pq.push({ d[next], next });
            }
        }
    }
    printf("%d", d[e]);

    return 0;
}
