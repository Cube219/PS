#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    struct Nxt { int nxt, w; };
    vector<vector<Nxt>> g(n);
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u].push_back({ v, w });
        g[v].push_back({ u, w });
    }

    int st, ed;
    cin >> st >> ed;
    st--; ed--;

    struct PQNode
    {
        int cur;
        ll cost, acost;
        bool operator<(const PQNode& rhs) const
        {
            if(cost == rhs.cost) return acost < rhs.acost;
            return cost > rhs.cost;
        }
    };
    priority_queue<PQNode> pq;
    vector<ll> dis(n, LNF), water(n, 0);
    dis[st] = 0;
    water[st] = a[st];
    pq.push({ st, 0, a[st] });
    while(!pq.empty()) {
        auto [cur, cost, acost] = pq.top(); pq.pop();
        if(dis[cur] != cost || water[cur] != acost) continue;

        for(auto [nxt, c] : g[cur]) {
            if(dis[nxt] > cost + c || (dis[nxt] == cost + c && water[nxt] < acost + a[nxt])) {
                dis[nxt] = cost + c;
                water[nxt] = acost + a[nxt];
                pq.push({ nxt, dis[nxt], water[nxt] });
            }
        }
    }

    if(dis[ed] == LNF) cout << "-1";
    else cout  << dis[ed] << " " << water[ed];
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
