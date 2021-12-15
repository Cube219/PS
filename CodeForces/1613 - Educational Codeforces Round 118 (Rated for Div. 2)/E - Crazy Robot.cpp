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
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        int n, m;
        cin >> n >> m;

        vector<string> map(n);
        for(int i = 0; i < n; ++i) {
            cin >> map[i];
        }
        vector<vector<int>> d(n, vector<int>(m, 0));

        queue<pair<int, int>> q;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                for(int k = 0; k < 4; ++k) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

                    if(map[nx][ny] == '.' || map[nx][ny] == 'L') d[i][j]++;
                }
                if(map[i][j] == 'L') q.push({ i, j });
            }
        }

        vector<vector<char>> visit(n, vector<char>(m, false));

        while(q.size() > 0) {
            auto [x, y] = q.front();
            q.pop();

            visit[x][y] = true;

            for(int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(visit[nx][ny] == true) continue;
                if(map[nx][ny] == '#' || map[nx][ny] == 'L') continue;

                d[nx][ny]--;
                if(d[nx][ny] == 1 || d[nx][ny] == 0) {
                    q.push({ nx, ny });
                }
            }
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(map[i][j] != '.') cout << map[i][j];
                else {
                    if(visit[i][j]) cout << "+";
                    else cout << ".";
                }
            }
            cout << "\n";
        }
    }

    return 0;
}
