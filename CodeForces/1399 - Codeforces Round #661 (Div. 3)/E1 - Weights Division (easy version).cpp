#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <queue>
#include <vector>

using lli = long long int;

int tNum;
int n;
lli s;
int res;

struct EdgeInfo
{
    int numLeaves;
    int weight;
};
std::vector<std::pair<int, int>> g[100005];
EdgeInfo edges[100005];

bool isVisited[100005];
lli currentSum;

struct PQInfo
{
    lli value;
    int numLeaves;
    int weight;
};
auto cmp = [](const PQInfo& l, const PQInfo& r) {
    if(l.value == r.value) return l.numLeaves < r.numLeaves;
    else return l.value < r.value;
};
std::priority_queue<PQInfo, std::vector<PQInfo>, decltype(cmp)> pq(cmp);

int make(int node, lli cSum)
{
    isVisited[node] = true;

    bool isLeaf = true;
    int leaveNum = 0;

    for(auto child : g[node]) {
        if(isVisited[child.first] == true) continue;

        isLeaf = false;

        edges[child.first].weight = child.second;

        leaveNum += make(child.first, cSum + (lli)(child.second));
    }

    if(isLeaf == true) {
        leaveNum = 1;
        currentSum += cSum;
    }

    edges[node].numLeaves = leaveNum;

    return leaveNum;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        res = 0;
        currentSum = 0;

        scanf("%d %lld", &n, &s);

        for(int i = 1; i <= n; i++) {
            g[i].clear();
            isVisited[i] = false;
        }
        while(pq.empty() == false) pq.pop();

        for(int i = 0; i < n - 1; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            g[u].push_back({ v, w });
            g[v].push_back({ u, w });
        }

        make(1, 0);

        for(int i = 2; i <= n; i++) {
            lli v = (lli)edges[i].numLeaves * (lli)edges[i].weight - (lli)edges[i].numLeaves * (lli)(edges[i].weight / 2);
            pq.push({ v, edges[i].numLeaves, edges[i].weight });
        }

        while(currentSum > s) {
            auto info = pq.top();
            pq.pop();

            currentSum -= (lli)(info.numLeaves) * (lli)(info.weight);

            info.weight /= 2;
            info.value = (lli)info.numLeaves * (lli)info.weight - (lli)info.numLeaves * (lli)(info.weight / 2);
            currentSum += (lli)(info.numLeaves) * (lli)(info.weight);

            res++;

            pq.push(info);
        }

        printf("%d\n", res);
    }

    return 0;
}
