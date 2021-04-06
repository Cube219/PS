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

int n;
vector<pair<int, ll>> g[100001];
ll fuel[100001];
bool visit[100001];
int sz[100001];
int minDep[1000001];
ll res;
vector<ll> in, out, inall, outall;

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

void getin(int cur, int p, ll curFuel, ll reqFuel)
{
    curFuel += fuel[cur];
    if(reqFuel <= fuel[cur] && curFuel >= 0) {
        in.push_back(curFuel);
    }
    reqFuel = max(0ll, reqFuel - fuel[cur]);
    for(auto& [nxt, cost] : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        getin(nxt, cur, curFuel - cost, reqFuel + cost);
    }
}

void getout(int cur, int p, ll reqFuel, ll preMax)
{
    preMax = max(preMax, reqFuel);
    out.push_back(preMax);
    reqFuel -= fuel[cur];

    for(auto& [nxt, cost] : g[cur]) {
        if(nxt == p || visit[nxt] == true) continue;
        getout(nxt, cur, reqFuel + cost, preMax);
    }
}

void centroid(int cur, int p)
{
    int size = getSize(cur, -1);
    int cen = getCenter(cur, -1, size);
    visit[cen] = true;

    inall.clear();
    outall.clear();
    inall.push_back(fuel[cen]);
    outall.push_back(0);

    for(auto& [nxt, cost] : g[cen]) {
        if(nxt == p || visit[nxt] == true) continue;
        in.clear();
        out.clear();

        getin(nxt, cen, -cost, cost);
        getout(nxt, cen, cost, 0);

        for(int i = 0; i < in.size(); ++i) {
            if(in[i] >= 0) in[i] += fuel[cen];
        }

        sort(in.begin(), in.end());
        sort(out.begin(), out.end());
        for(int i = 0; i < in.size(); ++i) {
            int idx = upper_bound(out.begin(), out.end(), in[i]) - out.begin();
            res -= idx;
        }

        inall.insert(inall.end(), in.begin(), in.end());
        outall.insert(outall.end(), out.begin(), out.end());
    }
    sort(inall.begin(), inall.end());
    sort(outall.begin(), outall.end());
    for(int i = 0; i < inall.size(); ++i) {
        // if(inall[i] >= 0) res++;
        int idx = upper_bound(outall.begin(), outall.end(), inall[i]) - outall.begin();
        res += idx;
    }
    res--; // 자기자신을 빼줌

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

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> fuel[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    centroid(0, -1);

    if(res == INF) res = -1;
    cout << res;

    return 0;
}
