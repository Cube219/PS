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

int n, m;
int map[501][501];
int sx, sy;
vector<int> g[250001];

int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int dy[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

ll v[250001];
bool comp[250001];
ll d[250001];

ll process()
{
    ll res = 0;
    int cur = m * sx + sy;
    priority_queue<pair<ll, int>> pq;
    pq.push({ d[cur], cur });
    d[cur] = v[cur];
    while(pq.empty() == false) {
        cur = pq.top().second;
        pq.pop();
        if(comp[cur] == true) continue;

        comp[cur] = true;
        d[cur] = min(d[cur], v[cur]);
        res += d[cur];
        for(int nxt : g[cur]) {
            if(comp[nxt] == true) continue;
            if(d[nxt] < d[cur]) {
                d[nxt] = d[cur];
                pq.push({ d[nxt], nxt });
            }
        }
    }
    return res;
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
        for(int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }
    cin >> sx >> sy;
    sx--; sy--;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] >= 0) continue;
            int cnum = i * m + j;
            v[cnum] = -map[i][j];
            for(int k = 0; k < 8; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(map[nx][ny] >= 0) continue;
                int nnum = m * nx + ny;
                g[cnum].push_back(nnum);
            }
        }
    }

    cout << process();

    return 0;
}
