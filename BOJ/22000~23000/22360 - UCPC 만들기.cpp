#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

using ll = long long int;

int n;
vector<int> g[200001];
char d[200005];
bool visit[200001];
int sz[200001];
ll res;

int getSize(int cur, int p)
{
    sz[cur] = 1;
    for(int nxt : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        sz[cur] += getSize(nxt, cur);
    }
    return sz[cur];
}
int getCenter(int cur, int p, int size)
{
    for(int nxt : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        if(sz[nxt] > size / 2) return getCenter(nxt, cur, size);
    }
    return cur;
}

void search(int cur, int par, int u, int c, int p, map < pair<int, int>, ll> & mp)
{
    if(d[cur] == 'U') u++;
    else if(d[cur] == 'C') c++;
    else p++;
    auto it = mp.find({ u - p, u + p - c });
    if(it == mp.end()) {
        it = mp.insert({ {u - p, u + p - c}, 0 }).first;
    }
    it->second++;

    for(int nxt : g[cur]) {
        if(nxt == par || visit[nxt] == true) continue;
        search(nxt, cur, u, c, p, mp);
    }
}

void centroid(int cur, int par)
{
    int size = getSize(cur, -1);
    int cen = getCenter(cur, -1, size);

    visit[cen] = true;
    int u = 0, c = 0, p = 0;
    if(d[cen] == 'U') u++;
    else if(d[cen] == 'C') c++;
    else p++;

    map<pair<int, int>, ll> curmp;
    curmp.insert({ {0, 0}, 1 });
    for(int nxt : g[cen]) {
        if(visit[nxt] == true) continue;
        map<pair<int, int>, ll> newmp;

        search(nxt, cen, 0, 0, 0, newmp);

        if(curmp.size() < newmp.size()) swap(curmp, newmp);
        for(auto& v : newmp) {
            int v1 = v.first.first + u - p;
            int v2 = v.first.second + u + p - c;
            auto it = curmp.find({ -v1, -v2 });
            if(it != curmp.end()) {
                res += v.second * it->second;
            }
        }
        for(auto& v : newmp) {
            int v1 = v.first.first;
            int v2 = v.first.second;
            auto it = curmp.find({ v1, v2 });
            if(it == curmp.end()) {
                it = curmp.insert({ {v1, v2}, 0 }).first;
            }
            it->second += v.second;
        }
    }

    for(int nxt : g[cen]) {
        if(nxt == par || visit[nxt] == true) continue;
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

    cin >> n;
    cin >> d;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    centroid(0, -1);

    cout << res;

    return 0;
}
