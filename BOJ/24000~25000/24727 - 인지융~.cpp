#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, c, e;
    cin >> n >> c >> e;

    vector<vector<int>> res(n, vector<int>(n, -1));
    for(int i = 0; i < n * 2; ++i) {
        if(c == 0) break;
        for(int j = 0; i - j >= 0 && j < n; ++j) {
            if(i - j >= n) continue;
            if(c == 0) break;
            res[i - j][j] = 1;
            c--;
        }
    }
    vector<int> dx = { 1, 0, -1, 0 }, dy = { 0, 1, 0, -1 };
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(res[i][j] != 1) continue;
            for(int k = 0; k < 4; ++k) {
                int x = i + dx[k];
                int y = j + dy[k];
                if(x < 0 || y < 0 || x >= n || y >= n) continue;
                if(res[x][y] == -1) res[x][y] = -2;
            }
        }
    }

    queue<pair<int, int>> q;
    if(res[n-1][n-1] == -1) {
        q.push({ n - 1, n - 1 });
        res[n - 1][n - 1] = 2;
        e--;
    }
    while(!q.empty() && e > 0) {
        auto [x, y] = q.front();
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if(res[nx][ny] == -1 && e > 0) {
                res[nx][ny] = 2;
                e--;
                q.push({ nx, ny });
            }
        }
    }

    if(c > 0 || e > 0) cout << "-1";
    else {
        cout << "1\n";
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(res[i][j] < 0) res[i][j] = 0;
                cout << res[i][j];
            }
            cout << "\n";
        }
    }
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
