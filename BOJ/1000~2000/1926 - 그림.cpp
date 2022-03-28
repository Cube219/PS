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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> d(n, vector<int>(m));
    for(auto& v1 : d) for(auto& v2 : v1) cin >> v2;

    vector<int> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };
    auto bfs = [&](int x, int y) {
        queue<pair<int, int>> q;
        int res = 0;

        q.push({ x, y });
        d[x][y] = 2;
        while(q.empty() == false) {
            auto [cx, cy] = q.front();
            q.pop();

            res++;

            for(int i = 0; i < 4; ++i) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(d[nx][ny] != 1) continue;

                d[nx][ny] = 2;
                q.push({ nx, ny });
            }
        }
        return res;
    };

    int cnt = 0, mx = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(d[i][j] != 1) continue;
            cnt++;
            mx = max(mx, bfs(i, j));
        }
    }

    cout << cnt << "\n" << mx;
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
