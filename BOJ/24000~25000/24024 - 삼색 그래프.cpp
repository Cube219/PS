#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m, x;
    cin >> n >> m >> x;
    struct Node
    {
        int nxt, cost, color;
    };
    vector<vector<Node>> g(n);
    for(int i = 0; i < m; ++i) {
        int u, v, w, p;
        cin >> u >> v >> w >> p;
        u--; v--;
        g[u].push_back({ v, w, p });
        g[v].push_back({ u, w, p });
    }

    vector<ll> dst;
    vector<char> visit;
    int red = 0, blue = 0;
    auto dijk = [&](int n, int st) -> void {
        dst.clear();
        dst.resize(n, LNF);
        visit.clear();
        visit.resize(n, false);
        dst[st] = 0;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        pq.push({ 0, st });
        while(pq.empty() == false) {
            int cur = pq.top().second;
            pq.pop();
            if(visit[cur] == true) continue;

            visit[cur] = true;
            for(auto [nxt, cost, color] : g[cur]) {
                if(color == 1) cost += red;
                else if(color == 2) cost += blue;

                if(visit[nxt] == false && dst[nxt] > dst[cur] + cost) {
                    dst[nxt] = dst[cur] + cost;
                    pq.push({ dst[nxt], nxt });
                }
            }
        }
    };

    auto tsearch = [](ll minx, ll maxx, const function<ll(ll)>& tfunc) {
        ll l = minx, r = maxx;
        while(l + 2 < r) {
            ll p = (l * 2 + r) / 3;
            ll q = (l + r * 2) / 3;

            ll pv = tfunc(p);
            ll qv = tfunc(q);

            if(pv <= qv) l = p;
            else r = q;
        }

        ll res = tfunc(l);
        for(ll i = l + 1; i <= r; ++i) {
            res = max(res, tfunc(i));
        }
        return res;
    };

    auto tf = [&](ll k) {
        red = k;
        blue = x - k;
        dijk(n, 0);

        return dst[n - 1];
    };

    cout << tsearch(0, x, tf);
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
