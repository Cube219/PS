#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

struct Edge
{
    int nxt;
    ll p;
};

struct QNode
{
    int cur;
    ll d;
};
bool operator<(const QNode& l, const QNode& r)
{
    return l.d > r.d;
}

int n, m;
vector<Edge> g[500001];
ll sum[500001];
ll dst[500001];
map<pair<int, int>, int> exNode;
int nodenum;
priority_queue<QNode> pq;

int getnode(int node, int color)
{
    auto it = exNode.find({ node, color });
    if(it == exNode.end()) {
        it = exNode.insert({ {node, color}, nodenum++ }).first;
    }
    return it->second;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    nodenum = n;
    for(int i = 0; i < m; ++i) {
        int u, v, c;
        ll p;
        cin >> u >> v >> c >> p;
        u--; v--;

        int ucolNode = getnode(u, c);
        int vcolNode = getnode(v, c);
        sum[ucolNode] += p;
        sum[vcolNode] += p;

        g[u].push_back({ v, p });
        g[v].push_back({ u, p });

        g[ucolNode].push_back({ v, -p });
        g[vcolNode].push_back({ u, -p });

        g[u].push_back({ vcolNode, 0 });
        g[v].push_back({ ucolNode, 0 });
    }

    for(auto& it : exNode) {
        int u = it.first.first;
        int colNode = it.second;
        g[u].push_back({ colNode, 0 });
        for(auto& nxt : g[colNode]) {
            nxt.p += sum[colNode];
        }
    }

    for(int i = 0; i < nodenum; ++i) {
        dst[i] = INF;
    }
    pq.push({ 0, 0 });
    dst[0] = 0;
    while(pq.empty() == false) {
        QNode cur = pq.top();
        pq.pop();
        if(dst[cur.cur] != cur.d) continue;

        for(auto& nx : g[cur.cur]) {
            int nxt = nx.nxt;
            ll cost = nx.p;
            if(dst[nxt] > dst[cur.cur] + cost) {
                dst[nxt] = dst[cur.cur] + cost;
                pq.push({ nxt, dst[nxt] });
            }
        }
    }
    ll res = dst[n - 1];
    if(res == INF) res = -1;
    cout << res;

    return 0;
}
