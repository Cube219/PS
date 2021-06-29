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
constexpr ll INF = 9999999999999;

int n, m;
int map[31][31];
int sx, sy, ex, ey;
vector<int> g[1001];
bool visit[31][31];
queue<pair<int, int>> q;
queue<pair<int, ll>> q2;
ll d[1001], cnt[1001];

int dx[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

void mk(int x, int y)
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            visit[i][j] = false;
        }
    }

    int base = x * m + y;
    q.push({ x, y });
    visit[x][y] = true;
    while(q.empty() == false) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for(int i = 0; i < 8; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || visit[nx][ny] == true) continue;
            if(map[nx][ny] == 2) continue;
            visit[nx][ny] = true;
            if(map[nx][ny] == 1) {
                q.push({ nx, ny });
            } else {
                int idx = nx * m + ny;
                g[base].push_back(idx);
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
        for(int j = 0; j < m; ++j) {
            cin >> map[i][j];
            if(map[i][j] == 3) {
                sx = i; sy = j;
            } else if(map[i][j] == 4) {
                ex = i; ey = j;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 1 || map[i][j] == 2) continue;
            mk(i, j);
        }
    }

    for(int i = 0; i < n * m; ++i) {
        d[i] = INF;
    }
    int st = sx * m + sy;
    int ed = ex * m + ey;
    q2.push({ st, 0 });
    d[st] = 0;
    cnt[st] = 1;
    while(q2.empty() == false) {
        int cur = q2.front().first;
        ll cost = q2.front().second;
        q2.pop();
        if(d[cur] != cost) continue;
        if(cost > d[ed]) break;

        for(int nxt : g[cur]) {
            if(d[nxt] > cost + 1) {
                d[nxt] = cost + 1;
                cnt[nxt] = cnt[cur];
                q2.push({ nxt, d[nxt] });
            } else if(d[nxt] == cost + 1) {
                cnt[nxt] += cnt[cur];
            }
        }
    }

    if(d[ed] == INF) {
        cout << "-1";
    } else {
        cout << d[ed] - 1 << "\n" << cnt[ed];
    }

    return 0;
}
