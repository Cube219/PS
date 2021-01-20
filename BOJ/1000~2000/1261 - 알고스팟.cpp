#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int n, m;
vector<pair<int, int>> g[10001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[10001];
bool isVisited[10001];

char map[101][101];

void process()
{
    for(int i = 0; i < n * m; i++) {
        d[i] = 2147483647;
    }

    d[0] = 0;
    pq.push({ 0, 0 });
    while(pq.empty() == false) {
        int current = 0;
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
    scanf("%d %d", &m, &n);
    for(int i = 0; i < n; i++) {
        scanf("%s", map[i]);
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int index = i * m + j;
            int cost = 0;

            if(j < m - 1) {
                cost = map[i][j + 1] - '0';
                g[index].push_back({ i * m + (j + 1), cost });
            }
            if(i < n - 1) {
                cost = map[i + 1][j] - '0';
                g[index].push_back({ (i + 1) * m + j, cost });
            }
            if(j > 0) {
                cost = map[i][j - 1] - '0';
                g[index].push_back({ i * m + (j - 1), cost });
            }
            if(i > 0) {
                cost = map[i - 1][j] - '0';
                g[index].push_back({ (i - 1) * m + j, cost });
            }
        }
    }

    process();

    printf("%d", d[n * m - 1]);

    return 0;
}
