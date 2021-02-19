#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

using ll = long long int;

int n, m;
vector<pair<int, int>> g[5100001];

void make_edge(int a, int b, int cost)
{
    g[a * 51].push_back({ b * 51 + cost, 0 });
    for(int i = 1; i <= 50; ++i) {
        int c = cost + i;
        c = c * c;
        g[b * 51 + i].push_back({a * 51, c});
    }
}

priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
ll d[5100001];
bool finish[5100001];
constexpr ll INF = 99999999999999;
void dij()
{
    for(int i = 1; i <= n * 51; ++i) {
        d[i] = INF;
    }

    pq.push({ 0, 0 });
    while(pq.empty() == false) {
        int cur = pq.top().second;
        pq.pop();

        if(finish[cur] == true) continue;

        finish[cur] = true;

        for(auto& nx : g[cur]) {
            int nxt = nx.first;
            ll cost = nx.second;

            if(finish[nxt] == true) continue;

            if(d[nxt] > d[cur] + cost) {
                d[nxt] = d[cur] + cost;
                pq.push({ d[nxt], nxt });
            }
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        make_edge(a, b, c);
        make_edge(b, a, c);
    }

    dij();

    for(int i = 0; i < n; ++i) {
        if(d[i * 51] == INF) d[i * 51] = -1;
        cout << d[i * 51] << " ";
    }

    return 0;
}
