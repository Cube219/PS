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

struct Polygon
{
    int x[3];
    int y[3];
    int z[3];
};

struct Edge
{
    int u, v, w;
};

struct Point
{
    int x, y, z;
};
bool operator==(const Point& l, const Point& r)
{
    return l.x == r.x && l.y == r.y && l.z == r.z;
}

int n;
Polygon d[2012];
vector<pair<int, Point>> g[2012];
int gr[2012][2012];
int stx, sty, stz, edx, edy, edz;
vector<Point> res;
int resdis;
int st, ed;

vector<Edge> e;
int parent[2012], rnk[2012], dis[2012];
int find(int v)
{
    while(parent[v] != v) v = parent[v];
    return v;
}
void uni(int u, int v, int w)
{
    int ur = find(u);
    int vr = find(v);
    if(ur == vr) return;
    if(rnk[ur] > rnk[vr]) swap(ur, vr);
    parent[ur] = vr;
    if(rnk[ur] == rnk[vr]) rnk[vr]++;
    dis[ur] = w;
}
int query(int u, int v)
{
    if(find(u) != find(v)) return -1;
    int ret = 0;
    while(u != v) {
        if(dis[u] > dis[v]) swap(u, v);
        ret = dis[u];
        u = parent[u];
    }
    return ret;
}

ll sign(Point p1, Point p2, Point p3)
{
    return (ll)(p1.x - p3.x) * (ll)(p2.y - p3.y) - (ll)(p2.x - p3.x) * (ll)(p1.y - p3.y);
}

bool PointInTriangle(Point pt, Point v1, Point v2, Point v3)
{
    ll  d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

ll bfsdis[2012];
int pre[2012];
Point precost[2012];
void bfs()
{
    for(int i = 0; i < n; ++i) {
        bfsdis[i] = 99999999999999999;
    }
    queue<int> q;
    q.push(st);
    bfsdis[st] = 0;
    while(q.empty() == false) {
        int cur = q.front();
        if(cur == ed) break;
        q.pop();

        for(auto& [nxt, cost] : g[cur]) {
            if(cost.z > resdis) continue;
            if(bfsdis[nxt] > bfsdis[cur] + cost.z) {
                bfsdis[nxt] = bfsdis[cur] + cost.z;
                pre[nxt] = cur;
                precost[nxt] = cost;
                q.push(nxt);
            }
        }
    }
    int cur = ed;
    res.push_back({ edx, edy, edz });
    while(cur != st) {
        res.push_back(precost[cur]);
        cur = pre[cur];
    }
    res.push_back({ stx, sty, stz });
    reverse(res.begin(), res.end());
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x[0] >> d[i].y[0] >> d[i].z[0];
        cin >> d[i].x[1] >> d[i].y[1] >> d[i].z[1];
        cin >> d[i].x[2] >> d[i].y[2] >> d[i].z[2];
    }
    cin >> stx >> sty >> stz;
    cin >> edx >> edy >> edz;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            gr[i][j] = INF;
        }
    }

    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            Polygon& p1 = d[i];
            Polygon& p2 = d[j];
            for(int k = 0; k < 3; ++k) {
                for(int l = 0; l < 3; ++l) {
                    if(p1.x[k] == p2.x[l] && p1.y[k] == p2.y[l] && p1.z[k] == p2.z[l]) {
                        gr[i][j] = min(gr[i][j], p1.z[k]);
                        gr[j][i] = min(gr[j][i], p1.z[k]);
                        Point gn = { p1.x[k], p1.y[k], p1.z[k] };
                        g[i].push_back({ j, gn });
                        g[j].push_back({ i, gn });
                    }
                }
            }
        }
    }

    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            if(gr[i][j] != INF) {
                e.push_back({ i, j, gr[i][j] });
            }
        }
    }
    sort(e.begin(), e.end(), [](const auto& l, const auto& r) {
        return l.w < r.w;
    });
    for(int i = 0; i < n; ++i) {
        dis[i] = 987654321;
        parent[i] = i;
    }
    for(int i = 0; i < e.size(); ++i) {
        uni(e[i].u, e[i].v, e[i].w);
    }

    st = -1, ed = -1;
    Point stP = { stx, sty, 0 };
    Point edP = { edx, edy, 0 };
    for(int i = 0; i < n; ++i) {
        Point p1 = { d[i].x[0], d[i].y[0], 0 };
        Point p2 = { d[i].x[1], d[i].y[1], 0 };
        Point p3 = { d[i].x[2], d[i].y[2], 0 };
        if(st == -1 && PointInTriangle(stP, p1, p2, p3)) {
            st = i;
        }
        if(ed == -1 && PointInTriangle(edP, p1, p2, p3)) {
            ed = i;
        }
    }

    resdis = query(st, ed);

    bfs();

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); ++i) {
        cout << res[i].x << " " << res[i].y << " " << res[i].z << "\n";
    }

    return 0;
}
