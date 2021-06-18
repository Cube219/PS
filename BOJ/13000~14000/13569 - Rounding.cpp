#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999;

template <int N>
class Flow
{
public:
    struct Edge
    {
        int dst;
        ll c;
        ll f;
        int revIdx;
    };

    vector<Edge> g[N + 1];
    int n;
    int level[N + 1];
    int work[N + 1];

    void init(int _n)
    {
        n = _n;
        for(int i = 0; i < n; ++i) {
            g[i].clear();
        }
    }

    void addEdge(int s, int e, ll c, bool biDir = false)
    {
        Edge e1 = { e, c, 0, -1 };
        Edge e2 = { s, 0, 0, -1 };
        if(biDir == true) e2.c = c;
        e1.revIdx = g[e].size();
        e2.revIdx = g[s].size();
        g[s].push_back(e1);
        g[e].push_back(e2);
    }

    void addFlow(Edge& e, ll f)
    {
        e.f += f;
        g[e.dst][e.revIdx].f -= f;
    }

    bool initLevel(int st, int ed)
    {
        for(int i = 0; i < n; ++i) {
            level[i] = -1;
        }
        level[st] = 0;
        queue<int> q;
        q.push(st);
        while(q.empty() == false) {
            int cur = q.front();
            q.pop();
            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                ll c = nx.c;
                ll f = nx.f;
                if(level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        if(level[ed] == -1) return false;
        return true;
    }

    ll flow(int cur, int ed, ll minFlow)
    {
        if(cur == ed) return minFlow;

        for(int i = work[cur]; i < g[cur].size(); ++i) {
            auto& nx = g[cur][i];
            int nxt = nx.dst;
            ll c = nx.c;
            ll f = nx.f;
            if(level[nxt] == level[cur] + 1 && c > f) {
                ll res = flow(nxt, ed, min(minFlow, c - f));
                if(res > 0) {
                    addFlow(nx, res);
                    return res;
                }
            }
            work[cur]++;
        }
        return 0;
    }

    ll maxFlow(int st, int ed)
    {
        ll res = 0;
        while(1) {
            if(initLevel(st, ed) == false) break;
            for(int i = 0; i < n; ++i) {
                work[i] = 0;
            }
            while(1) {
                ll f = flow(st, ed, INF);
                if(f == 0) break;
                res += f;
            }
        }

        return res;
    }
};


int n, m;
double d[201][201], rsum[201], csum[201];
Flow<100001> f;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    /// freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> d[i][j];
        }
        cin >> rsum[i];
    }
    for(int i = 0; i < m; ++i) {
        cin >> csum[i];
    }
    f.init((n + 1) * (m + 1) * 2 + 5);
    int st = (n + 1) * (m + 1) * 2;
    int ed = st + 1;
    vector<pair<int, ll>> neg, pos;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int idx = i * m + j;
            ll low = (ll)d[i][j];
            ll high = ceil(d[i][j]);

            f.addEdge(idx * 2, idx * 2 + 1, high - low);
            neg.push_back({ idx * 2 + 1, -low });
            pos.push_back({ idx * 2, low });
        }
    }
    int cur = n * m * 2;
    ll streq = 0, edreq = 0;
    for(int i = 0; i < n; ++i) {
        ll low = (ll)rsum[i];
        ll high = ceil(rsum[i]);

        f.addEdge(st, cur, high - low);
        streq += low;
        neg.push_back({ cur, -low });
        for(int j = 0; j < m; ++j) {
            int idx = i * m + j;
            f.addEdge(cur, idx * 2, INF);
        }
        cur++;
    }
    for(int j = 0; j < m; ++j) {
        ll low = (ll)csum[j];
        ll high = ceil(csum[j]);

        f.addEdge(cur, ed, high - low);
        edreq -= low;
        pos.push_back({ cur, low });
        for(int i = 0; i < n; ++i) {
            int idx = i * m + j;
            f.addEdge(idx * 2 + 1, cur, INF);
        }
        cur++;
    }
    f.addEdge(ed, st, INF);
    pos.push_back({ st, streq });
    neg.push_back({ ed, edreq });
    int st2 = ed + 1;
    int ed2 = st2 + 1;
    for(int i = 0; i < neg.size(); ++i) {
        if(neg[i].second == 0) continue;
        f.addEdge(st2, neg[i].first, -neg[i].second);
    }
    for(int i = 0; i < pos.size(); ++i) {
        if(pos[i].second == 0) continue;
        f.addEdge(pos[i].first, ed2, pos[i].second);
    }

    f.maxFlow(st2, ed2);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int idx = i * m + j;
            cout << f.g[idx * 2][0].f + (ll)d[i][j] << " ";
        }
        cout << f.g[st][i].f + (ll)rsum[i] << "\n";
    }
    cur = n * m * 2 + n;
    for(int i = 0; i < m; ++i) {
        cout << f.g[cur][0].f + (ll)csum[i] << " ";
        cur++;
    }

    return 0;
}
