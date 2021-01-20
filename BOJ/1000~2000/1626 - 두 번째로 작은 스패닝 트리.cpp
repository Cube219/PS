#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge
{
    int a;
    int b;
    int cost;
};
bool operator<(const Edge& l, const Edge& r)
{
    return l.cost < r.cost;
}

using Tree = std::vector<std::vector<std::pair<int, int>>>;
using Table = std::vector<std::vector<int>>;

int n, m;
Edge edges[200001];
std::vector<Edge> remainEdges;
Tree tree;
int parents[50002][21];
int maxCosts[50002][21];
int sMaxCosts[50002][21];
int depths[50001];

int Find(int x, std::vector<int>& d)
{
    if(d[x] == x) return x;
    int res = Find(d[x], d);
    d[x] = res;
    return res;
}

void Uni(int x, int y, std::vector<int>& d)
{
    int xSet = Find(x, d);
    int ySet = Find(y, d);

    if(xSet == ySet) return;

    d[xSet] = ySet;
}

int MST()
{
    std::vector<int> sets;
    sets.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        sets[i] = i;
    }

    tree.resize(n + 1);

    int res = 0;
    int cnt = 0;
    std::sort(edges, edges + m);
    for(int i = 0; i < m; i++) {
        Edge& e = edges[i];

        int aSet = Find(e.a, sets);
        int bSet = Find(e.b, sets);
        if(aSet == bSet) {
            remainEdges.push_back(e);
            continue;
        }

        Uni(e.a, e.b, sets);
        res += e.cost;
        cnt++;

        tree[e.a].push_back(std::make_pair(e.b, e.cost));
        tree[e.b].push_back(std::make_pair(e.a, e.cost));

        if(cnt >= n - 1) {
            i++;
            while(i < m) {
                remainEdges.push_back(edges[i]);
                i++;
            }
            break;
        }
    }

    int fs = Find(1, sets);
    for(int i = 2; i <= n; i++) {
        if(fs != Find(i, sets)) {
            res = -1;
            break;
        }
    }

    return res;
}

void GenerateTree(int node, int depth)
{
    depths[node] = depth;
    for(auto& child : tree[node]) {
        int c = child.first;

        if(depths[c] == 0) {
            parents[c][0] = node;
            maxCosts[c][0] = child.second;
            GenerateTree(c, depth + 1);
        }
    }
}

void GenerateTables()
{
    for(int i = 0; i < 20; i++) {
        for(int j = 1; j <= n; j++) {
            int upperIdx = parents[j][i];
            if(upperIdx != 0) {
                parents[j][i + 1] = parents[upperIdx][i];
                maxCosts[j][i + 1] = std::max(maxCosts[j][i], maxCosts[upperIdx][i]);

                if(maxCosts[j][i] == maxCosts[upperIdx][i]) {
                    sMaxCosts[j][i + 1] = std::max(sMaxCosts[j][i], sMaxCosts[upperIdx][i]);
                } else {
                    sMaxCosts[j][i + 1] = std::min(maxCosts[j][i], maxCosts[upperIdx][i]);
                }
            }
        }
    }
}

int FindMaxInCycle(int a, int b, int cost)
{
    if(depths[a] > depths[b]) std::swap(a, b);

    int gap = depths[b] - depths[a];

    int res = -1;

    int idx = 0;
    while(gap > 0) {
        if(gap % 2 == 1) {
            if(maxCosts[b][idx] == cost) res = std::max(res, sMaxCosts[b][idx]);
            else res = std::max(res, maxCosts[b][idx]);
            b = parents[b][idx];
        }
        idx++;
        gap /= 2;
    }

    if(a != b) {
        for(int i = 19; i >= 0; i--) {
            if(parents[a][i] != 0 && parents[b][i] != 0 && parents[a][i] != parents[b][i]) {
                if(maxCosts[a][i] == cost) res = std::max(res, sMaxCosts[a][i]);
                else res = std::max(res, maxCosts[a][i]);
                a = parents[a][i];

                if(maxCosts[b][i] == cost) res = std::max(res, sMaxCosts[b][i]);
                else res = std::max(res, maxCosts[b][i]);
                b = parents[b][i];
            }
        }
        if(maxCosts[a][0] < cost) res = std::max(res, maxCosts[a][0]);
        if(maxCosts[b][0] < cost) res = std::max(res, maxCosts[b][0]);
    }

    return res;
}

int main(int argc, char** argv)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i].a = a;
        edges[i].b = b;
        edges[i].cost = c;
    }

    if(m <= n - 1) {
        cout << "-1\n";
        return 0;
    }

    int mst;
    mst = MST();
    if(mst == -1) {
        cout << "-1\n";
        return 0;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 20; j++) {
            parents[i][j] = 0;
            maxCosts[i][j] = 0;
            sMaxCosts[i][j] = -1;
        }
    }
    parents[1][0] = 1;
    maxCosts[1][0] = -1;
    sMaxCosts[1][0] = 0;
    GenerateTree(1, 1);

    GenerateTables();

    int res = 2147483647;

    for(auto it = remainEdges.begin(); it != remainEdges.end(); it++) {
        Edge& e = *it;

        int v = FindMaxInCycle(e.a, e.b, e.cost);
        if(v == e.cost || v == -1) continue;

        if(res > mst + e.cost - v) {
            res = mst + e.cost - v;
        }
    }

    if(res == 2147483647) res = -1;
    std::cout << res << std::endl;

    return 0;
}
