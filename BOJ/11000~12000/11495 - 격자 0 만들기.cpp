#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

struct Edge
{
    int dst, c, f, revIdx;
};
vector<Edge> g[2505];
void addE(int s, int e, int c)
{
    Edge e1 = { e, c, 0, -1 };
    Edge e2 = { s, 0, 0, -1 };
    e1.revIdx = g[e].size();
    e2.revIdx = g[s].size();
    g[s].push_back(e1);
    g[e].push_back(e2);
}
void flow(Edge& e, int f)
{
    e.f += f;
    g[e.dst][e.revIdx].f -= f;
}
int pre[2505];
Edge* path[2505];

int tNum;
int n, m;
int d[51][51];
int res;

void initGraph()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int num = i * m + j + 1;
            g[num].clear();
        }
    }
    int ed = m * n + 1;
    g[0].clear();
    g[ed].clear();
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int num = i * m + j + 1;
            if((i + j) % 2 == 0) {
                addE(0, num, d[i][j]);
                // right
                if(j < m - 1) {
                    addE(num, num + 1, 987654321);
                }
                // left
                if(j > 0) {
                    addE(num, num - 1, 987654321);
                }
                // down
                if(i < n - 1) {
                    addE(num, num + m, 987654321);
                }
                // up
                if(i > 0) {
                    addE(num, num - m, 987654321);
                }
            } else {
                addE(num, ed, d[i][j]);
            }
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cin >> d[i][j];
            }
        }
        res = 0;
        initGraph();

        int st = 0, ed = (n * m + 1);
        while(1) {
            queue<int> q;
            q.push(st);
            for(int i = 0; i <= ed; ++i) {
                pre[i] = -1;
            }
            while(q.empty() == false && pre[ed] == -1) {
                int cur = q.front();
                q.pop();
                for(auto& nx : g[cur]) {
                    int nxt = nx.dst;
                    int c = nx.c;
                    int f = nx.f;
                    if(c > f && pre[nxt] == -1) {
                        pre[nxt] = cur;
                        path[nxt] = &nx;
                        q.push(nxt);
                        if(nxt == ed) break;
                    }
                }
            }
            if(pre[ed] == -1) break;
            int idx = ed;
            int ff = 987654321;
            while(idx != st) {
                ff = min(ff, path[idx]->c - path[idx]->f);
                idx = pre[idx];
            }
            idx = ed;
            while(idx != st) {
                flow(*path[idx], ff);
                idx = pre[idx];
            }
            res += ff;
        }

        for(auto& node : g[0]) {
            if(node.c == 0) continue;
            res += node.c - node.f;
        }
        for(auto& node : g[ed]) {
            if(node.c != 0) continue;
            auto& revNode = g[node.dst][node.revIdx];
            res += revNode.c - revNode.f;
        }
        cout << res << "\n";
    }

    return 0;
}
