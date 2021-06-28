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
constexpr ll INF = 99999999999999;

int n, m, k;
vector<pair<int, ll>> g[1001];

priority_queue<ll> dst[1001];

void dijk(int st)
{
    dst[st].push(0);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        ll curcost = pq.top().first;
        pq.pop();

        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll nxtcost = nx.second;

            if(dst[nxt].size() < k) {
                dst[nxt].push(curcost + nxtcost);
                pq.push({ curcost + nxtcost, nxt });
            } else if(dst[nxt].top() > curcost + nxtcost) {
                dst[nxt].pop();
                dst[nxt].push(curcost + nxtcost);
                pq.push({ curcost + nxtcost, nxt });
            }
        }
    }
}


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
    }

    dijk(0);
    for(int i = 0; i < n; ++i) {
        if(dst[i].size() < k) cout << "-1\n";
        else cout << dst[i].top() <<"\n";
    }

    return 0;
}
