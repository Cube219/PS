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
constexpr ll INF = 99999999999999999;

struct Node
{
    int nxt;
    ll cost;
    int idx;
};

int n, m, lo, hi;
vector<Node> g[100001];

ll dst[100001];
bool visit[100001];

void dijk(int st)
{
    for(int i = 0; i < n; ++i) {
        dst[i] = INF;
        visit[i] = false;
    }
    dst[st] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({ 0, st });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();
        if(visit[cur] == true) continue;

        visit[cur] = true;
        for(auto& nx : g[cur]) {
            int nxt = nx.nxt;
            int cost = nx.cost;

            if(visit[nxt] == false && dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                pq.push({ dst[nxt], nxt });
            }
        }
    }
}

bool use[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> lo >> hi;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        c *= 2;
        g[a].push_back({ b, c, i });
        g[b].push_back({ a, c, i });
    }

    dijk(0);
    for(int i = 0; i < n; ++i) {
        if(dst[i] < hi) {
            for(auto& nx : g[i]) {
                use[nx.idx] = true;
            }
        }
    }
    int res = 0;
    for(int i = 0; i < m; ++i) {
        if(use[i] == true) res++;
    }
    cout << res;

    return 0;
}
