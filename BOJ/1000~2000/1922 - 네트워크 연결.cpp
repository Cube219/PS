#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

struct Edge
{
    int a;
    int b;
    int cost;
};
bool operator<(const Edge& l, const Edge& r)
{
    return l.cost < r.cost;
}

int n, m;
int cnt, res;
Edge edges[100001];
int sets[1001];

int Find(int x)
{
    if(sets[x] == x) return x;
    int res = Find(sets[x]);
    sets[x] = res;
    return res;
}

void Uni(int x, int y)
{
    int xSet = Find(x);
    int ySet = Find(y);

    if(xSet == ySet) return;

    sets[xSet] = ySet;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i].a = a;
        edges[i].b = b;
        edges[i].cost = c;
    }
    for(int i = 1; i <= n; i++) {
        sets[i] = i;
    }
    sort(edges, edges + m);
    for(int i = 0; i < m; i++) {
        Edge& e = edges[i];
        if(e.a == e.b) continue;

        int aSet = Find(e.a);
        int bSet = Find(e.b);
        if(aSet == bSet) continue;

        Uni(e.a, e.b);
        res += e.cost;
        cnt++;

        if(cnt >= n - 1) break;
    }

    cout << res;

    return 0;
}
