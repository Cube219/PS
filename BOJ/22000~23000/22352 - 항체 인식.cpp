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

int n, m;
int m1[31][31], m2[31][31];
bool area[31][31], comp[31][31];
int cnt;
bool pos = true;
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };

void ck(int x, int y)
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            area[i][j] = false;
        }
    }
    queue<pair<int, int>> q;
    q.push({ x, y });

    int color = m1[x][y];
    area[x][y] = true;
    comp[x][y] = true;

    while(q.empty() == false) {
        auto cur = q.front();
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nx = cur.first + dx[i];
            int ny = cur.second + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if(m1[nx][ny] != color || area[nx][ny] == true) continue;
            q.push({ nx, ny });
            area[nx][ny] = true;
            comp[nx][ny] = true;
        }
    }

    color = -1;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(area[i][j] == false) continue;
            if(color == -1) color = m2[i][j];
            else if(color != m2[i][j]) {
                pos = false;
                return;
            }
        }
    }
    if(color != m1[x][y]) cnt++;
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
            cin >> m1[i][j];
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> m2[i][j];
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(comp[i][j] == true) continue;
            ck(i, j);
        }
    }

    if(cnt > 1) pos = false;

    if(pos == true) cout << "YES";
    else cout << "NO";

    return 0;
}
