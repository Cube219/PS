#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n, k;
vector<pair<int, ll>> g[200001];
bool visit[200001];
int sz[200001];
int minDep[1000001];
int res = INF;
vector<int> rb;

int getSize(int cur, int p)
{
    sz[cur] = 1;
    for(auto& [nxt, cost] : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        sz[cur] += getSize(nxt, cur);
    }
    return sz[cur];
}
int getCenter(int cur, int p, int size)
{
    for(auto& [nxt, cost] : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        if(sz[nxt] > size / 2) return getCenter(nxt, cur, size);
    }
    return cur;
}

void search(int cur, int p, ll dis, int dep)
{
    if(minDep[k - dis] != INF) {
        res = min(res, minDep[k - dis] + dep);
    }
    for(auto& [nxt, cost] : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        if(dis + cost > k) continue;
        search(nxt, cur, dis + cost, dep + 1);
    }
}

void update(int cur, int p, ll dis, int dep)
{
    minDep[dis] = min(minDep[dis], dep);
    rb.push_back(dis);

    for(auto& [nxt, cost] : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        if(dis + cost > k) continue;
        update(nxt, cur, dis + cost, dep + 1);
    }
}

void centroid(int cur, int p)
{
    int size = getSize(cur, -1);
    int cen = getCenter(cur, -1, size);

    for(int i = 0; i < rb.size(); ++i) {
        minDep[rb[i]] = INF;
    }
    rb.clear();

    visit[cen] = true;
    for(auto& [nxt, cost] : g[cen]) {
        if(visit[nxt] == true) continue;
        if(cost > k) continue;
        search(nxt, cen, cost, 1);
        update(nxt, cen, cost, 1);
    }

    for(auto& [nxt, cost] : g[cen]) {
        if(nxt == p || visit[nxt] == true) continue;
        centroid(nxt, cen);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    for(int i = 1; i <= k; ++i) {
        minDep[i] = INF;
    }

    centroid(0, -1);

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
