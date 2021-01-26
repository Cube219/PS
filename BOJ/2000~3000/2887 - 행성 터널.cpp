#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
struct Point
{
    int idx;
    int x;
    int y;
    int z;
};

Point d[100001];

struct Edge
{
    int a;
    int b;
    ll cost;
};
vector<Edge> edges;

int f[100001];
ll res;
int cnt;

void addEdge(int flags)
{
    for(int i = 0; i < n - 1; i++) {
        int a = d[i].idx;
        int b = d[i + 1].idx;
        ll cost = abs(d[i].x - d[i + 1].x);
        cost = min(cost, (ll)abs(d[i].y - d[i + 1].y));
        cost = min(cost, (ll)abs(d[i].z - d[i + 1].z));
        edges.push_back({ a, b, cost });
    }
}

int find(int a)
{
    if(f[a] == a) return a;

    int res = find(f[a]);
    f[a] = res;
    return res;
}

void uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return;

    f[ar] = br;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d[i].x >> d[i].y >> d[i].z;
        d[i].idx = i;
        f[i] = i;
    }
    sort(d, d + n, [](const Point& l, const Point& r) {
        return l.x < r.x;
    });
    addEdge(0);
    
    sort(d, d + n, [](const Point& l, const Point& r) {
        return l.y < r.y;
    });
    addEdge(1);
    
    sort(d, d + n, [](const Point& l, const Point& r) {
        return l.z < r.z;
    });
    addEdge(2);

    sort(edges.begin(), edges.end(), [](const Edge& l, const Edge& r) { return l.cost < r.cost; });

    for(int i=0; i < edges.size(); i++) {
        int a = edges[i].a;
        int b = edges[i].b;
        ll cost = edges[i].cost;

        int ar = find(a);
        int br = find(b);
        if(ar == br) continue;

        res += cost;
        uni(ar, br);
        cnt++;

        if(cnt == n - 1) break;
    }
    
    cout << res;
    
    return 0;
}
