#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <string>
#include <vector>
using namespace std;

using ll = long long int;

struct Edge
{
    int dst, c, f, revIdx;
};
vector<Edge> g[10002];
int pre[10002];
Edge* path[10002];
void addE(int s, int e, int c)
{
    Edge e1 = { e, c, 0, -1 };
    Edge e2 = { s, 0, 0, -1 };
    e1.revIdx = g[e].size();
    e2.revIdx = g[s].size();
    g[s].push_back(e1);
    g[e].push_back(e2);
}
void addF(Edge& e, int f)
{
    e.f += f;
    g[e.dst][e.revIdx].f -= f;
}

int tNum;
int k, n;
string str;
vector<int> d;
int cnt;
vector<vector<int>> res;

void init()
{
    res.clear();
    for(int i = 1; i <= n; ++i) {
        g[i * 2].clear();
        g[i * 2 + 1].clear();
    }
    cnt = 0;
}

void addEdge(int s, int e)
{
    addE(s * 2 + 1, e * 2, 1);
    // addE(e * 2 + 1, s * 2, 1);
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    tNum = 1;
    while(1) {
        cin >> k >> n;
        if(n == 0) break;
        init();
        getline(cin, str);
        for(int i = 1; i <= n; ++i) {
            getline(cin, str);
            d.clear();
            int curNum = 0;
            for(int j = 0; j < str.size(); ++j) {
                if(str[j] == ' ') {
                    d.push_back(curNum);
                    curNum = 0;
                    continue;
                }
                curNum *= 10;
                curNum += str[j] - '0';
            }
            if(curNum > 0) d.push_back(curNum);
            for(int j = 0; j < d.size(); ++j) {
                addEdge(i, d[j]);
            }
        }

        for(int i = 3; i <= n; ++i) {
            addE(i * 2, i * 2 + 1, 1);
        }

        int st = 3, ed = 4;
        while(1) {
            queue<int> q;
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
            int flow = 987654321;
            int idx = ed;
            while(idx != st) {
                flow = min(flow, path[idx]->c - path[idx]->f);
                idx = pre[idx];
            }
            idx = ed;
            while(idx != st) {
                addF(*path[idx], flow);
                idx = pre[idx];
            }
            cnt += flow;
        }

        if(cnt >= k) {
            for(int i = 0; i < k; ++i) {
                queue<int> q;
                q.push(st);
                for(int i = 1; i <= n; ++i) {
                    pre[i * 2] = -1;
                    pre[i * 2 + 1] = -1;
                }
                while(q.empty() == false && pre[ed] == -1) {
                    int cur = q.front();
                    q.pop();
                    for(auto& nx : g[cur]) {
                        int nxt = nx.dst;
                        int f = nx.f;
                        if(f > 0 && pre[nxt] == -1) {
                            pre[nxt] = cur;
                            path[nxt] = &nx;
                            q.push(nxt);
                            if(nxt == ed) break;
                        }
                    }
                }
                res.push_back({});
                auto& rr = res.back();
                int idx = ed;
                while(idx != st) {
                    if(idx % 2 == 0) rr.push_back(idx / 2);
                    path[idx]->f = 0;
                    idx = pre[idx];
                }
                rr.push_back(1);
            }
        }

        cout << "Case " << tNum << ":\n";
        if(res.size() < k) {
            cout << "Impossible\n";
        } else {
            for(int i = 0; i < k; ++i) {
                for(int j = res[i].size() - 1; j >= 0; --j) {
                    cout << res[i][j] << " ";

                }
                cout << "\n";
            }
        }
        cout << "\n";

        tNum++;
    }

    return 0;
}
