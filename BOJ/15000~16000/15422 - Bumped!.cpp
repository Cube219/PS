#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

using lli = long long int;
constexpr lli LLI_MAX = 9223372036854775807ll;

int n, m, s, e;
vector<pair<int, lli>> g[50001];
int fNum;
pair<int, int> f[1001];
lli d[50001];
bool isVisited[50001];

lli res;

void process()
{
    for(int i = 0; i < n; i++) {
        d[i] = LLI_MAX;
        isVisited[i] = false;
    }
    d[s] = 0;

    priority_queue<pair<lli, int>, vector<pair<lli, int>>, greater<pair<lli, int>>> pq;
    pq.push({0, s});
    while(pq.empty() == false) {
        int current = s;
        while(1) {
            current = pq.top().second;
            pq.pop();
            if(isVisited[current] == false) break;
            if(pq.empty()) break;
        }
        if(isVisited[current] == true) break;
        
        isVisited[current] = true;

        for(auto n : g[current]) {
            int next = n.first;
            lli cost = n.second;
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
    scanf("%d %d %d %d %d", &n, &m, &fNum, &s, &e);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }
    for(int i = 0; i < fNum; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        f[i] = { a, b };
    }

    process();
    res = d[e];
    
    for(int i = 0; i < fNum; i++) {
        lli cost = LLI_MAX;
        int src = f[i].first;
        int dst = f[i].second;

        for(auto iter = g[src].begin(); iter != g[src].end(); iter++) {
            if(iter->first == dst) {
                cost = iter->second;
                g[src].erase(iter);
                break;
            }
        }
        g[src].push_back({ dst, 0 });

        process();
        if(res > d[e]) res = d[e];

        for(auto iter = g[src].begin(); iter != g[src].end(); iter++) {
            if(iter->first == dst) {
                g[src].erase(iter);
                break;
            }
        }

        if(cost != LLI_MAX) {
            g[src].push_back({dst, cost});
        }
    }

    printf("%lld", res);

    return 0;
}
