#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

using ll = long long int;

int tNum;
int w, n;
struct Node
{
    int x;
    int y;
    int r;
};
Node d[1001];
struct Edge
{
    int a;
    int b;
    double cost;
};
vector<Edge> edges;

int p[1002];
double res;

int find(int a)
{
    if(p[a] == a) return a;
    int res = find(p[a]);
    p[a] = res;
    return res;
}

void uni(int a, int b)
{
    int ra = find(a);
    int rb = find(b);

    if(ra == rb) return;

    p[ra] = rb;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        edges.clear();

        cin >> w >> n;
        for(int i = 1; i <= n; ++i) {
            cin >> d[i].x >> d[i].y >> d[i].r;
            p[i] = i;
        }
        p[0] = 0;
        p[n + 1] = n + 1;
        res = w;

        for(int i = 1; i <= n; ++i) {
            int dis = d[i].x - d[i].r;
            // if(dis < 0) dis = 0;
            edges.push_back({ 0, i, (double)dis });

            dis = w - d[i].x - d[i].r;
            // if(dis < 0) dis = 0;
            edges.push_back({ n + 1, i, (double)dis });
        }

        for(int i = 1; i < n; ++i) {
            for(int j = i + 1; j <= n; ++j) {
                ll dx = abs(d[i].x - d[j].x);
                ll dy = abs(d[i].y - d[j].y);
                double dis = sqrt(dx * dx + dy * dy);
                dis -= (double)(d[i].r + d[j].r);
                // if(dis < 0.0) dis = 0.0;
                edges.push_back({ i, j, dis });
            }
        }

        sort(edges.begin(), edges.end(), [](const Edge& l, const Edge& r) { return l.cost < r.cost; });
        for(int i = 0; i < edges.size(); ++i) {
            int a = edges[i].a;
            int b = edges[i].b;
            double cost = edges[i].cost;

            int ra = find(a);
            int rb = find(b);
            if(ra == rb) continue;

            uni(ra, rb);

            int wa = find(0);
            int wb = find(n + 1);
            if(wa == wb) {
                if(cost < 0.0) res = 0;
                else res = cost;
                break;
            }
        }

        cout << fixed << res / 2.0 << "\n";
    }

    return 0;
}
