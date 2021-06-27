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

int n, m;
vector<pair<int, ll>> g[5001];

ll dst[5001], dst2[5001];

void dijk(int st)
{
    for(int i = 0; i < n; ++i) {
        dst[i] = INF;
        dst2[i] = INF;
    }
    dst[st] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        ll curdst = pq.top().first;
        pq.pop();
        if(dst2[cur] < curdst) continue;

        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cost = nx.second;

            ll nxtdst = curdst + cost;
            if(dst[nxt] > nxtdst) {
                dst2[nxt] = dst[nxt];
                dst[nxt] = nxtdst;
                pq.push({ nxtdst, nxt });
            } else if(dst2[nxt] > nxtdst) {
                dst2[nxt] = nxtdst;
                pq.push({ nxtdst, nxt });
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

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({ b, c });
        g[b].push_back({ a, c });
    }

    dijk(0);

    cout << dst2[n - 1];

    return 0;
}
