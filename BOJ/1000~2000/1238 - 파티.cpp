#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int n, m, x;
vector<pair<int, int>> g[1001];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int d[1001];
bool isVisited[1001];

int xTo[1001];

void Process(int start, int* const& arr, int end = -1)
{
    for(int i = 1; i <= n; i++) {
        arr[i] = 2147483647;
        isVisited[i] = false;
    }
    while(pq.empty() == false) pq.pop();

    arr[start] = 0;
    pq.push({ 0, start });
    while(pq.empty() == false) {
        int current = start;
        while(1) {
            current = pq.top().second;
            pq.pop();
            if(isVisited[current] == false || pq.empty()) break;
        }
        if(isVisited[current] == true) break;

        isVisited[current] = true;

        if(end != -1 && current == end) break;

        for(auto t : g[current]) {
            int next = t.first;
            int cost = t.second;
            if(isVisited[next] == true) continue;

            if(arr[next] > arr[current] + cost) {
                arr[next] = arr[current] + cost;
                pq.push({ arr[next], next });
            }
        }
    }
}

int main(void)
{
    scanf("%d %d %d", &n, &m, &x);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        g[a].push_back({ b, c });
    }

    Process(x, xTo);

    int max = 0;

    for(int i = 1; i <= n; i++) {
        Process(i, d, x);
        if(max < d[x] + xTo[i]) {
            max = d[x] + xTo[i];
        }
    }

    printf("%d", max);

    return 0;
}
