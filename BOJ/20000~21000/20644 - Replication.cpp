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

struct Point
{
    int x, y, time, size;
};

int n, d;
char map[1002][1002];
vector<pair<int, int>> st;
vector<pair<int, int>> rocks;
int dis[1001][1001], dis2[1001][1001];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
int res[1002][1002];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> d;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
        for(int j = 0; j < n; ++j) {
            if(map[i][j] == '#') rocks.push_back({ i, j });
            else {
                if(map[i][j] == 'S') st.push_back({ i, j });
                dis[i][j] = INF;
            }
        }
    }
    queue<Point> q;
    for(int i = 0; i < rocks.size(); ++i) {
        q.push({ rocks[i].first, rocks[i].second, 0, 0 });
    }
    while(q.empty() == false) {
        auto cur = q.front();
        int cx = cur.x;
        int cy = cur.y;
        q.pop();
        for(int j = 0; j < 4; ++j) {
            int nx = cx + dx[j];
            int ny = cy + dy[j];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(map[nx][ny] != '#' && dis[nx][ny] > dis[cx][cy] + 1) {
                dis[nx][ny] = dis[cx][cy] + 1;
                q.push({ nx, ny });
            }
        }
    }

    for(int i = 0; i < st.size(); ++i) {
        q.push({ st[i].first, st[i].second, 0, 1 });
    }

    while(q.empty() == false) {
        Point cur = q.front();
        q.pop();
        int cx = cur.x;
        int cy = cur.y;
        int ctime = cur.time;
        int csize = cur.size;
        res[cx][cy] = csize;
        for(int j = 0; j < 4; ++j) {
            int nx = cx + dx[j];
            int ny = cy + dy[j];
            int ntime = ctime + 1;
            int nsize = csize;
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(res[nx][ny] != 0 || map[nx][ny] == '#') continue;

            if(dis[nx][ny] >= nsize) {
                res[nx][ny] = nsize;
            }
            if(ntime % d == 0) {
                nsize++;
            }
            if(dis[nx][ny] >= nsize) {
                q.push({ nx, ny, ntime, nsize });
                res[nx][ny] = nsize;
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(res[i][j] != 0) {
                q.push({ i, j, 0, res[i][j] });
            }
        }
    }

    while(q.empty() == false) {
        Point cur = q.front();
        int cx = cur.x;
        int cy = cur.y;
        int csize = cur.size;
        q.pop();
        for(int j = 0; j < 4; ++j) {
            int nx = cx + dx[j];
            int ny = cy + dy[j];
            int nsize = csize - 1;
            if(nx < 0 || ny < 0 || nx >= n || ny >= n || nsize <= 0) continue;
            if(res[nx][ny] >= nsize || map[nx][ny] == '#') continue;
            res[nx][ny] = nsize;
            q.push({ nx, ny, 0, nsize });
        }
    }

    int cnt = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(res[i][j] > 0) cnt++;
        }
    }
    cout << cnt;

    return 0;
}
