#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

using ll = long long int;

struct Edge
{
    int a, b, cost;
};

int n;
Edge e[100001];
int order[100001];
vector<pair<int, int>> g[100001];
int v[100001];
ll res[100001], curres;
int parent[100001], rnk[100001];
map<int, int> xors[100001];

void dfs(int cur, int p, int curcost)
{
    for(auto& nx : g[cur]) {
        int nxt = nx.first;
        int cost = nx.second;
        if(nxt == p) continue;

        v[nxt] = curcost ^ cost;
        dfs(nxt, cur, v[nxt]);
    }
}

int find(int a)
{
    while(a != parent[a]) a = parent[a];
    return a;
}

void uni(int a, int b, int idx)
{
    int ap = find(a);
    int bp = find(b);
    if(rnk[ap] > rnk[bp]) {
        swap(a, b);
        swap(ap, bp);
    }
    for(auto axor : xors[ap]) {
        auto it = xors[bp].find(axor.first);
        if(it != xors[bp].end()) {
            curres += (ll)axor.second * it->second;
        }
    }
    res[idx] = curres;
    for(auto axor : xors[ap]) {
        auto it = xors[bp].find(axor.first);
        if(it == xors[bp].end()) {
            it = xors[bp].insert({ axor.first, 0 }).first;
        }
        it->second += axor.second;
    }
    xors[ap].clear();
    if(rnk[ap] == rnk[bp]) {
        rnk[bp]++;
    }
    parent[ap] = bp;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        e[i] = { a, b, c };
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }
    for(int i = 0; i < n; ++i) {
        cin >> order[i];
        order[i]--;
    }

    dfs(0, -1, 0);

    reverse(order, order + n - 1);
    for(int i = 0; i < n; ++i) {
        parent[i] = i;
        xors[i].insert({ v[i], 1 });
    }
    for(int i = 0; i < n - 1; ++i) {
        Edge& addEdge = e[order[i]];
        uni(addEdge.a, addEdge.b, i);
    }

    for(int i = n - 2; i >= 0; --i) {
        cout << res[i] << "\n";
    }
    cout << "0\n";

    return 0;
}
