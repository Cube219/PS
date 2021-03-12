#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
template<int N>
class Flow
{
public:
    struct Edge
    {
        int dst, c, f, revIdx;
    };
    vector<Edge> g[N + 1];
    int pre[N + 1];
    Edge* path[N + 1];

    void clear(int n)
    {
        for(int i = 1; i <= n; ++i) {
            g[i].clear();
        }
    }

    void addEdge(int s, int e, int c, bool biDir = false)
    {
        Edge e1 = { e, c, 0, -1 };
        Edge e2 = { s, 0, 0, -1 };
        if(biDir == true) e2.c = c;
        e1.revIdx = g[e].size();
        e2.revIdx = g[s].size();
        g[s].push_back(e1);
        g[e].push_back(e2);
    }

    void addFlow(Edge& e, int f)
    {
        e.f += f;
        g[e.dst][e.revIdx].f -= f;
    }

    int flow(int st, int ed)
    {
        for(int i = 0; i <= N; ++i) {
            pre[i] = -1;
        }
        queue<int> q;
        q.push(st);
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
        if(pre[ed] == -1) return 0;
        int flow = 987654321;
        int idx = ed;
        while(idx != st) {
            flow = min(flow, path[idx]->c - path[idx]->f);
            idx = pre[idx];
        }
        idx = ed;
        while(idx != st) {
            addFlow(*path[idx], flow);
            idx = pre[idx];
        }
        return flow;
    }

    int maxFlow(int st, int ed)
    {
        int res = 0;
        while(1) {
            int f = flow(st, ed);
            if(f == 0) break;
            res += f;
        }

        return res;
    }
};

Flow<302> f;
int n, m;
int cnt;

void init()
{
    f.clear(n);
    cnt = 0;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;

        init();

        for(int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            f.addEdge(a, b, c);
        }

        f.maxFlow(1, n);

        int ed = n;
        for(int i = 1; i <= n; ++i) {
            for(auto& e : f.g[i]) {
                if(e.c == e.f && e.c > 0) {
                    queue<int> q;
                    vector<Flow<302>::Edge*> pp;
                    for(int j = 1; j <= n; ++j) {
                        f.pre[j] = -1;
                    }
                    q.push(e.dst);
                    while(q.empty() == false && f.pre[ed] == -1) {
                        int cur = q.front();
                        q.pop();
                        for(auto& nx : f.g[cur]) {
                            int nxt = nx.dst;
                            int c = nx.c;
                            int fl = nx.f;
                            if(c > 0 && fl > 0 && f.pre[nxt] == -1) {
                                f.pre[nxt] = cur;
                                q.push(nxt);
                                pp.push_back(&nx);
                                if(nxt == ed) break;
                            }
                        }
                    }

                    for(int i = 0; i < pp.size(); ++i) {
                        pp[i]->f--;
                    }
                    e.f--;
                    e.c--;

                    // search alter path
                    for(int j = 1; j <= n; ++j) {
                        f.pre[j] = -1;
                    }
                    while(q.empty() == false) q.pop();
                    q.push(i);
                    while(q.empty() == false && f.pre[ed] == -1) {
                        int cur = q.front();
                        q.pop();
                        for(auto& nx : f.g[cur]) {
                            int nxt = nx.dst;
                            int c = nx.c;
                            int fl = nx.f;
                            if(c > fl && f.pre[nxt] == -1) {
                                f.pre[nxt] = cur;
                                q.push(nxt);
                                if(nxt == ed) break;
                            }
                        }
                    }
                    if(f.pre[ed] == -1) cnt++; // cannot find

                    for(int i = 0; i < pp.size(); ++i) {
                        pp[i]->f++;
                    }
                    e.f++;
                    e.c++;
                }
            }
        }
        cout << cnt << "\n";
    }

    return 0;
}
