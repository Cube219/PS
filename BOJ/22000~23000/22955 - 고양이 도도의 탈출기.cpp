#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999;

int n, m;
char map[1005][1005];
vector<pair<int, int>> g[1000001];
int st, ed;

ll dst[1000001];
bool visit[1000001];

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
            int nxt = nx.first;
            int cost = nx.second;

            if(visit[nxt] == false && dst[nxt] > dst[cur] + cost) {
                dst[nxt] = dst[cur] + cost;
                pq.push({ dst[nxt], nxt });
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
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int idx = i * m + j;
            if(map[i][j] == 'X' || map[i][j] == 'D') continue;

            if(map[i][j] == 'C') st = idx;
            else if(map[i][j] == 'E') ed = idx;

            if(map[i][j] == 'L' && i > 0) {
                int upidx = (i - 1) * m + j;
                g[idx].push_back({ upidx, 5 });
            }
            if(i + 1 < n && map[i + 1][j] == 'L') {
                int didx = (i + 1) * m + j;
                g[idx].push_back({ didx, 5 });
            }
            if(j > 0 && map[i][j - 1] != 'D') {
                int nidx = idx - 1;
                g[idx].push_back({ nidx, 1 });
            }
            if(j + 1 < m && map[i][j + 1] != 'D') {
                int nidx = idx + 1;
                g[idx].push_back({ nidx, 1 });
            }
        }
    }

    for(int j = 0; j < m; ++j) {
        int dstx = -1;
        for(int i = n - 2; i >= 0; --i) {
            if(map[i][j] == 'X') {
                if(dstx == -1) {
                    dstx = (i + 1) * m + j;
                }
                int cur = i * m + j;
                g[cur].push_back({ dstx, 10 });
            } else {
                dstx = -1;
            }
        }
    }

    n = n * m;
    dijk(st);

    ll res = dst[ed];
    if(res == INF) cout << "dodo sad";
    else cout << res;

    return 0;
}
