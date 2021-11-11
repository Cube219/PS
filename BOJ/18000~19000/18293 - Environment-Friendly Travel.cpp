#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

struct Edge
{
    int nxt, c, b;
};

struct Point
{
    int x, y;
};

struct Nxt
{
    int nxt, t;
};

struct PQNode
{
    int cur, cost, dis;
    bool operator<(const PQNode& rhs) const
    {
        return cost > rhs.cost;
    }
};

vector<Edge> g[1010];
int c[1010], b, t, n, c0, sti, edi;
Point st, ed;
Point pos[1011];
vector<Nxt> edge[1011];
int cost[1015][105];

int get_dis(Point a, Point b)
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int dis = dx * dx + dy * dy;

    for(int i = 0; i <= 1000; ++i) {
        if(i * i >= dis) return i;
    }
    return 0;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> st.x >> st.y >> ed.x >> ed.y;
    cin >> b >> c0;
    cin >> t;
    for(int i = 0; i < t; ++i) {
        cin >> c[i];
    }
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> pos[i].x >> pos[i].y >> num;
        edge[i].resize(num);
        for(int j = 0; j < num; ++j) {
            cin >> edge[i][j].nxt >> edge[i][j].t;
            edge[i][j].t--;
        }
    }
    edi = n;

    for(int i = 0; i < n; ++i) {
        int d = get_dis(pos[i], ed);
        if(d <= b) g[i].push_back({ edi, d * c0, d });

        for(auto& eg : edge[i]) {
            int d = get_dis(pos[i], pos[eg.nxt]);
            if(d > b) continue;
            g[i].push_back({ eg.nxt, d * c[eg.t], d });
            g[eg.nxt].push_back({ i, d * c[eg.t], d });
        }
    }

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j <= b; ++j) {
            cost[i][j] = INF;
        }
    }

    priority_queue<PQNode> pq;
    for(int i = 0; i < n; ++i) {
        int d = get_dis(st, pos[i]);
        if(d <= b) {
            pq.push({ i, d * c0, d });
            cost[i][d] = d * c0;
        }
    }
    {
        int d = get_dis(st, ed);
        if(d <= b) {
            pq.push({ edi, d * c0, d });
            cost[edi][d] = d * c0;
        }
    }
    int res = -1;
    while(pq.empty() == false) {
        auto cur = pq.top();
        pq.pop();

        if(cost[cur.cur][cur.dis] != cur.cost) continue;

        if(cur.cur == edi) {
            res = cur.cost;
            break;
        }

        for(auto& nx : g[cur.cur]) {
            int nxt = nx.nxt;
            int ncost = cur.cost + nx.c;
            int ndis = cur.dis + nx.b;

            if(ndis > b) continue;
            if(cost[nxt][ndis] > ncost) {
                cost[nxt][ndis] = ncost;
                pq.push({ nxt, ncost, ndis });
            }
        }
    }

    cout << res;

    return 0;
}
