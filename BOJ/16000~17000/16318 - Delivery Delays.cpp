#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999;

struct Order
{
    ll st, ed, dst;
};

int n, m, q;
vector<pair<int, ll>> g[1001];
Order order[1001];
ll cost[1001][1001];
ll dp[1001];

ll d[1001];
bool comp[1001];
void dijk(int st)
{
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    for(int i = 0; i < n; ++i) {
        d[i] = INF;
        comp[i] = false;
    }
    d[st] = 0;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(comp[cur] == true) continue;

        comp[cur] = true;
        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cost = nx.second;
            if(comp[nxt] == true) continue;
            if(d[nxt] > d[cur] + cost) {
                d[nxt] = d[cur] + cost;
                pq.push({ d[nxt], nxt });
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        cost[st][i] = d[i];
    }
}

bool ck(ll k)
{
    dp[0] = INF;
    if(order[0].ed + cost[0][order[0].dst] <= order[0].st + k) {
        dp[0] = order[0].ed + cost[0][order[0].dst];
    }
    for(int i = 1; i < q; ++i) {
        ll mvTime = 0;
        ll reqStTime = INF;
        dp[i] = INF;
        for(int j = i; j >= 0; --j) {
            ll stTime;
            if(j == 0) {
                stTime = order[i].ed;
            } else {
                stTime = max(order[i].ed, dp[j - 1] + cost[order[j - 1].dst][0]);
            }
            stTime += cost[0][order[j].dst];
            if(j == i) {
                reqStTime = order[j].st + k;
            } else {
                reqStTime = min(reqStTime - cost[order[j].dst][order[j + 1].dst], order[j].st + k);
                mvTime += cost[order[j].dst][order[j + 1].dst];
            }

            if(stTime <= reqStTime) {
                dp[i] = min(dp[i], stTime + mvTime);
            }
        }
    }
    if(dp[q - 1] >= INF) return false;
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cost[i][j] = INF;
        }
    }
    for(int i = 0; i < n; ++i) {
        dijk(i);
    }

    cin >> q;
    for(int i = 0; i < q; ++i) {
        int st, ed, dst;
        cin >> st >> dst >> ed;
        dst--;
        order[i] = { st, ed, dst };
    }

    ll l = 0, r = 4611686018427387904LL;
    while(l + 1 < r) {
        ll mid = (l + r) / 2;
        if(ck(mid) == true) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if(ck(l) == true) cout << l;
    else cout << r;

    return 0;
}
