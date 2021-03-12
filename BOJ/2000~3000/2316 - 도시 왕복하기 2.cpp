#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

int n, pNum;

struct Edge
{
    int dst, c, f, revIdx;
};
vector<Edge> g[802];
void add(int a, int b, int c)
{
    Edge e1 = { b, c, 0, -1 };
    Edge e2 = { a, 0, 0, -1 };
    e1.revIdx = g[b].size();
    e2.revIdx = g[a].size();
    g[a].push_back(e1);
    g[b].push_back(e2);
}
void flow(Edge& e, int f)
{
    e.f += f;
    g[e.dst][e.revIdx].f -= f;
}

queue<int> q;
int pre[802];
Edge* path[802];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> pNum;
    for(int i = 0; i < pNum; ++i) {
        int a, b;
        cin >> a >> b;
        a *= 2; b *= 2;
        add(a + 1, b, 1);
        add(b + 1, a, 1);
    }
    for(int i = 3; i <= n; ++i) {
        add(i * 2, i * 2 + 1, 1);
    }

    int st = 3, ed = 4;
    int res = 0;
    while(1) {
        while(q.empty() == false) q.pop();
        for(int i = 1; i <= n; ++i) {
            pre[i * 2] = -1;
            pre[i * 2 + 1] = -1;
        }

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

    cout << res;

    return 0;
}
