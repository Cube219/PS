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
constexpr int INF = 987654321;

struct Node
{
    int px, py, bx, by, push, move;
};
bool operator<(const Node& l, const Node& r)
{
    if(l.push == r.push) return l.move > r.move;
    return l.push > r.push;
}

int n, m;
char map[21][21];
int dis[21][21][21][21];
int dis2[21][21][21][21];
int rec[21][21][21][21];
char sym[] = { 'e', 's', 'w', 'n', 'E', 'S', 'W', 'N' };
int px, py, bx, by, tx, ty;
int rx, ry;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt = 0;
    while(1) {
        tt++;
        cin >> n >> m;
        if(n == 0) break;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cin >> map[i][j];
                if(map[i][j] == 'S') {
                    px = i; py = j;
                } else if(map[i][j] == 'B') {
                    bx = i; by = j;
                } else if(map[i][j] == 'T') {
                    tx = i; ty = j;
                }
            }
        }

        rx = -1;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                for(int k = 0; k < n; ++k) {
                    for(int l = 0; l < m; ++l) {
                        dis[i][j][k][l] = INF;
                        dis2[i][j][k][l] = INF;
                    }
                }
            }
        }
        dis[px][py][bx][by] = 0;
        dis2[px][py][bx][by] = 0;
        rec[px][py][bx][by] = -1;
        priority_queue<Node> pq;
        pq.push({ px, py, bx, by, 0, 0 });
        while(pq.empty() == false) {
            Node cur = pq.top();
            pq.pop();

            for(int i = 0; i < 4; ++i) {
                int nx = cur.px + dx[i];
                int ny = cur.py + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(map[nx][ny] == '#') continue;
                if(nx == cur.bx && ny == cur.by) {
                    int bnx = cur.bx + dx[i];
                    int bny = cur.by + dy[i];
                    if(bnx < 0 || bny < 0 || bnx >= n || bny >= m) continue;
                    if(map[bnx][bny] == '#') continue;

                    int nxpush = dis[nx][ny][bnx][bny];
                    int nxmove = dis2[nx][ny][bnx][bny];
                    if(nxpush > cur.push + 1 || (nxpush == cur.push + 1 && nxmove > cur.move + 1)) {
                        dis[nx][ny][bnx][bny] = cur.push + 1;
                        dis2[nx][ny][bnx][bny] = cur.move + 1;
                        rec[nx][ny][bnx][bny] = i + 4;
                        pq.push({ nx, ny, bnx, bny, cur.push + 1, cur.move + 1 });
                    }
                    if(bnx == tx && bny == ty) {
                        rx = nx;
                        ry = ny;
                        break;
                    }
                } else {
                    int nxpush = dis[nx][ny][cur.bx][cur.by];
                    int nxmove = dis2[nx][ny][cur.bx][cur.by];
                    if(nxpush > cur.push || (nxpush == cur.push && nxmove > cur.move + 1)) {
                        dis[nx][ny][cur.bx][cur.by] = cur.push;
                        dis2[nx][ny][cur.bx][cur.by] = cur.move + 1;
                        rec[nx][ny][cur.bx][cur.by] = i;
                        pq.push({ nx, ny, cur.bx, cur.by, cur.push, cur.move + 1 });
                    }
                }
            }
            if(rx != -1) break;
        }

        cout << "Maze #" << tt << "\n";
        if(rx == -1) {
            cout << "Impossible.\n\n";
            continue;
        }
        vector<char> res;
        while(rec[rx][ry][tx][ty] != -1) {
            int v = rec[rx][ry][tx][ty];
            res.push_back(sym[v]);
            if(v >= 4) {
                v -= 4;
                rx -= dx[v];
                ry -= dy[v];
                tx -= dx[v];
                ty -= dy[v];
            } else {
                rx -= dx[v];
                ry -= dy[v];
            }
        }
        for(int i = res.size() - 1; i >= 0; --i) {
            cout << res[i];
        }
        cout << "\n\n";
    }

    return 0;
}
