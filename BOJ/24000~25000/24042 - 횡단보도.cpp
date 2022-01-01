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
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    struct Node
    {
        int dst;
        ll time;
    };
    int n, m;
    cin >> n >> m;
    vector<vector<Node>> g(n);
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back({ b, (ll)i });
        g[b].push_back({ a, (ll)i });
    }

    vector<ll> dst;
    vector<char> visit;
    auto dijk = [&](int n, int st) -> void {
        dst.resize(n, LNF);
        visit.resize(n, false);
        dst[st] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({ 0, st });
        while(pq.empty() == false) {
            int cur = pq.top().second;
            ll time = pq.top().first;
            pq.pop();
            if(visit[cur] == true) continue;

            visit[cur] = true;
            ll cycle = time / m;
            time = time % m;

            for(auto& nx : g[cur]) {
                int nxt = nx.dst;
                int ntime = nx.time;

                ll v = cycle * m + ntime;
                if(ntime < time) v += m;

                if(visit[nxt] == false && dst[nxt] > v) {
                    dst[nxt] = v;
                    pq.push({ dst[nxt], nxt });
                }
            }
        }
    };
    dijk(n, 0);

    cout << dst[n - 1] + 1;
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
