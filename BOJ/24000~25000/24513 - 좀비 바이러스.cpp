#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> d(n, vector<int>(m));
    for(auto& v1 : d) for(auto& v2 : v1) cin >> v2;

    vector<int> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };
    struct Node
    {
        int x, y, col;
    };
    queue<Node> q;
    vector<vector<char>> comp(n, vector<char>(m, false));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(d[i][j] != 0) comp[i][j] = true;
            if(d[i][j] == 1 || d[i][j] == 2) {
                q.push({ i, j, d[i][j] });
            }
        }
    }

    while(!q.empty()) {
        vector<Node> tmp;
        while(!q.empty()) {
            auto [x, y, _] = q.front();
            q.pop();
            if(d[x][y] != 1 && d[x][y] != 2) continue;

            for(int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(d[nx][ny] != 0) continue;

                tmp.push_back({ nx, ny, d[x][y] });
            }
        }
        // cout << tmp.size() << "\n";

        for(auto [x, y, col] : tmp) {
            d[x][y] |= col;
            if(comp[x][y] == false) {
                q.push({ x, y, 0 });
                comp[x][y] = true;
            }
        }
    }

    int r1 = 0, r2 = 0, r3 = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(d[i][j] == 1) r1++;
            else if(d[i][j] == 2) r2++;
            else if(d[i][j] == 3) r3++;
        }
    }
    cout << r1 << " " << r2 << " " << r3;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
