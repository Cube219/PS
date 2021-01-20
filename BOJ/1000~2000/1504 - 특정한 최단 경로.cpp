#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int n, m, v1, v2;
vector<pair<int, int>> g[801];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[801];
bool isVisited[801];

constexpr int IMAX = 10000000;

void process(int start)
{
    while(pq.empty() == false) {
        pq.pop();
    }

    for(int i = 1; i <= n; i++) {
        d[i] = IMAX;
        isVisited[i] = false;
    }
    d[start] = 0;
    pq.push({ 0, start });

    while(pq.empty() == false) {
        int current;
        while(1) {
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
}

int main(void)
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }
    scanf("%d %d", &v1, &v2);

    process(1);
    int oneToV1 = d[v1];
    int oneToV2 = d[v2];
    
    process(v1);
    int v1ToV2 = d[v2];
    int v1ToN = d[n];

    process(v2);
    int v2ToV1 = d[v1];
    int v2ToN = d[n];

    int res = oneToV1 + v1ToV2 + v2ToN;
    int res2 = oneToV2 + v2ToV1 + v1ToN;

    if(res >= IMAX && res2 >= IMAX) {
        printf("-1");
    } else if(res < res2) {
        printf("%d", res);
    } else {
        printf("%d", res2);
    }

    return 0;
}
