#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, q;
vector<int> g[200001];
bool isCycle[200001];

bool isVisited[200001];
bool findCycle;
int endCycleNode;
vector<int> cycleNodes;
int colors[200001];

void c(int node, int beforeNode)
{
    isVisited[node] = true;

    for(auto next : g[node]) {
        if(next == beforeNode) continue;
        
        if(isVisited[next] == true) {
            endCycleNode = next;
            findCycle = true;
            break;
        }

        c(next, node);

        if(findCycle != 0) break;
    }

    if(endCycleNode != 0) {
        isCycle[node] = true;
        cycleNodes.push_back(node);
    }
    if(endCycleNode == node) {
        endCycleNode = 0;
    }
}

void f(int node, int beforeNode, int color)
{
    colors[node] = color;
    for(auto next : g[node]) {
        if(next == beforeNode) continue;
        if(isCycle[next] == true) continue;

        f(next, node, color);
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    c(1, -1);

    for(int i = 0; i < cycleNodes.size(); i++) {
        f(cycleNodes[i], -1, i);
    }

    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        if(colors[a] != colors[b]) cout << "2\n";
        else cout << "1\n";
    }

    return 0;
}
