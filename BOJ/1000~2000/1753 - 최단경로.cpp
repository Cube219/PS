#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int v, e, start;
vector<pair<int, int>> g[20001];
bool f[20001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[20001];

int main(void)
{
    scanf("%d %d %d", &v, &e, &start);
    for(int i = 0; i < e; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g[a].push_back({ b, c });
    }

    for(int i = 1; i <= v; i++) {
        d[i] = 2147483647;
    }
    d[start] = 0;

    pq.push({ 0, start });
    while(pq.empty() == false) {
        int nextV = start;
        while(1) {
            nextV = pq.top().second;
            pq.pop();
            if(f[nextV] == false) break;
            if(pq.empty()) break;
        }

        if(f[nextV] == true) break;

        f[nextV] = true;
        for(auto v2 : g[nextV]) {
            if(f[v2.first] == true) continue;

            if(d[nextV] + v2.second < d[v2.first]) {
                d[v2.first] = d[nextV] + v2.second;
                pq.push({d[v2.first], v2.first});
            }
        }
    }

    for(int i = 1; i <= v; i++) {
        if(d[i] == 2147483647) printf("INF\n");
        else printf("%d\n", d[i]);
    }

    return 0;
}
