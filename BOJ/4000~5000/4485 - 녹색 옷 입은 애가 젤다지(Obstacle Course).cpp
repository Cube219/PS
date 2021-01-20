#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int n;
vector<pair<int, int>> g[16000];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[16000];
bool isVisited[16000];
int a[126][126];

int main(void)
{
    int pCount = 0;
    while(1) {
        scanf("%d", &n);
        if(n == 0) break;
        pCount++;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                scanf("%d", &a[i][j]);
            }
        }

        for(int i = 0; i < n * n; i++) g[i].clear();

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int index = i * n + j;
                if(j + 1 < n) {
                    g[index].push_back({ index + 1, a[i][j + 1] });
                }
                if(i + 1 < n) {
                    g[index].push_back({ index + n, a[i + 1][j] });
                }
                if(j - 1 >= 0) {
                    g[index].push_back({ index - 1, a[i][j - 1] });
                }
                if(i - 1 >= 0) {
                    g[index].push_back({ index - n, a[i - 1][j] });
                }
            }
        }

        for(int i = 0; i < n * n; i++) {
            d[i] = 2147483647;
            isVisited[i] = false;
        }
        while(pq.empty() == false) {
            pq.pop();
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

        printf("Problem %d: %d\n", pCount, a[0][0] + d[n * n - 1]);
    }

    return 0;
}
