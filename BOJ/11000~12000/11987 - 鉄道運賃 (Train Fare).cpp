#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct Node
{
    int cost;
    int time;
    bool operator<(const Node& rhs) const
    {
        if(cost == rhs.cost) return time > rhs.time;
        return cost < rhs.cost;
    }
};

int n, m, q;
vector<pair<int, int>> g[100001];
pair<int, int> eg[200001];
bool use[200001];
int res[200001];

Node dst[100001];
bool visit[100001];

void dijk(int st)
{
    for(int i = 0; i < n; ++i) {
        dst[i] = { INF, 0 };
        visit[i] = false;
    }
    dst[st] = { 0, INF };
    priority_queue<pair<Node, int>, vector<pair<Node, int>>, greater<pair<Node, int>>> pq;
    pq.push({ dst[st], st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(visit[cur] == true) continue;

        visit[cur] = true;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            int time = nx.second;

            if(visit[nxt] == true) continue;

            if(dst[nxt].cost > dst[cur].cost + 1) {
                dst[nxt].cost = dst[cur].cost + 1;
                int t = min(dst[cur].time, time);
                dst[nxt].time = t;
                pq.push({ dst[nxt], nxt });
            } else if(dst[nxt].cost == dst[cur].cost + 1) {
                int t = min(dst[cur].time, time);
                dst[nxt].time = max(dst[nxt].time, t);
                pq.push({ dst[nxt], nxt });
            }
        }
    }
}


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        eg[i] = { a, b };
    }

    for(int i = 0; i < q; ++i) {
        int idx;
        cin >> idx;
        idx--;

        int u = eg[idx].first;
        int v = eg[idx].second;
        g[u].push_back({ v, i });
        g[v].push_back({ u, i });
        use[idx] = true;
    }
    for(int i = 0; i < m; ++i) {
        if(use[i] == true) continue;
        int u = eg[i].first;
        int v = eg[i].second;
        g[u].push_back({ v, INF });
        g[v].push_back({ u, INF });
    }

    dijk(0);

    for(int i = 1; i < n; ++i) {
        if(dst[i].time == INF) continue;
        res[dst[i].time]++;
    }

    for(int i = 0; i < q; ++i) {
        cout << res[i] << "\n";

        res[i + 1] += res[i];
    }

    return 0;
}
