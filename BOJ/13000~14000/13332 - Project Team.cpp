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

template <int N>
class Flow
{
public:
    struct Edge
    {
        int dst;
        int c;
        int f;
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
                int c = nx.c;
                int f = nx.f;
                if(level[nxt] == -1 && c > f) {
                    level[nxt] = level[cur] + 1;
                    q.push(nxt);
                }
            }
        }
        if(level[ed] == -1) return false;
        return true;
    }

    int flow(int cur, int ed, int minFlow)
    {
        if(cur == ed) return minFlow;

        for(int i = work[cur]; i < g[cur].size(); ++i) {
            auto& nx = g[cur][i];
            int nxt = nx.dst;
            int c = nx.c;
            int f = nx.f;
            if(level[nxt] == level[cur] + 1 && c > f) {
                int res = flow(nxt, ed, min(minFlow, c - f));
                if(res > 0) {
                    addFlow(nx, res);
                    return res;
                }
            }
            work[cur]++;
        }
        return 0;
    }

    int maxFlow(int st, int ed)
    {
        int res = 0;
        while(1) {
            if(initLevel(st, ed) == false) break;
            for(int i = 0; i < n; ++i) {
                work[i] = 0;
            }
            while(1) {
                int f = flow(st, ed, INF);
                if(f == 0) break;
                res += f;
            }
        }

        return res;
    }
};

struct Plan
{
    int d, r1, r2;
};

int m, n, p1, p2, q1[101], q2[101];
vector<Plan> plan[101];
Flow<13000> f;
int demand[13001];
int member[101];
vector<int> pnode[101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n >> p1 >> p2;
    for(int i = 0; i < n; ++i) {
        cin >> q1[i] >> q2[i];
    }
    int cnt = 0;
    for(int i = 0; i < m; ++i) {
        int num;
        cin >> num;
        cnt += num;
        plan[i].resize(num);
        for(int j = 0; j < num; ++j) {
            int d, r1, r2;
            cin >> d >> r1 >> r2;
            r1--; r2--;
            plan[i][j] = { d, r1, r2 };
        }
    }

    f.init(n + m + cnt + 5);

    int st = n + m + cnt;
    int ed = st + 1;
    for(int i = 0; i < n; ++i) {
        int low = m - q2[i];
        int high = m - q1[i];
        f.addEdge(i, ed, high - low);
        demand[i] += low;
        demand[ed] -= low;
    }
    int cur = n;
    int plow = n - p2;
    int phigh = n - p1;
    for(int i = 0; i < m; ++i) {
        member[i] = cur;
        f.addEdge(st, member[i], phigh - plow);
        demand[st] += plow;
        demand[member[i]] -= plow;
        cur++;
        for(int j = 0; j < plan[i].size(); ++j) {
            pnode[i].push_back(cur);
            auto& p = plan[i][j];
            int low = p.d;
            int high = p.r2 - p.r1 + 1;
            f.addEdge(member[i], cur, high - low);
            demand[member[i]] += low;
            demand[cur] -= low;
            for(int k = p.r1; k <= p.r2; ++k) {
                f.addEdge(cur, k, 1);
            }
            cur++;
        }
    }
    f.addEdge(ed, st, INF);
    int st2 = ed + 1;
    int ed2 = st2 + 1;
    int sum = 0;
    for(int i = 0; i <= ed; ++i) {
        if(demand[i] < 0) {
            f.addEdge(st2, i, -demand[i]);
        } else if(demand[i] > 0) {
            sum += demand[i];
            f.addEdge(i, ed2, demand[i]);
        }
    }

    int res = f.maxFlow(st2, ed2);
    if(res != sum) {
        cout << "-1";
    } else {
        cout << "1\n";
        vector<vector<int>> res(m);
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < pnode[i].size(); ++j) {
                auto& node = f.g[pnode[i][j]];
                for(int k = 0; k < node.size(); ++k) {
                    if(node[k].f == 1) {
                        res[i].push_back(node[k].dst + 1);
                    }
                }
            }
        }
        for(int i = 0; i < m; ++i) {
            cout << res[i].size() << " ";
            for(int j = 0; j < res[i].size(); ++j) {
                cout << res[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
