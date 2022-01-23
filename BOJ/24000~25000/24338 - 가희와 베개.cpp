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
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> map(n);
    for(auto& v : map)
        cin >> v;
    int stx, sty;
    cin >> stx >> sty;
    stx--;
    sty--;

    vector<vector<int>> d(n, vector<int>(m, -1));
    vector<int> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};
    auto dfs = [&](auto&& self, int x, int y, int curid) -> bool {
        int h = map[x][y] == '1' ? 1 : 0;
        d[x][y] = curid;
        bool ret = false;
        for(int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m)
                continue;

            if(d[nx][ny] != -1 || map[nx][ny] == '?' || map[nx][ny] == '#')
                continue;

            int nh = map[nx][ny] == '1' ? 1 : 0;
            if(h != nh)
                continue;

            bool r = self(self, nx, ny, curid);
            if(r == true)
                ret = true;
        }
        if(map[x][y] == 'P' || map[x][y] == 'B')
            ret = true;

        return ret;
    };
    vector<char> node;
    vector<pair<int, int>> eg;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == '?') {
                eg.emplace_back(i, j);
            }
            if(d[i][j] != -1 || map[i][j] == '#' || map[i][j] == '?')
                continue;
            bool r = dfs(dfs, i, j, node.size());
            node.push_back(r);
        }
    }

    vector<vector<int>> g(node.size());
    vector<int> visit(node.size(), 0);
    int cnt = 0;
    auto cango = [&]() {
        cnt++;
        queue<int> q;
        q.push(d[stx][sty]);
        visit[d[stx][sty]] = cnt;

        bool res = false;
        while(q.empty() == false) {
            int cur = q.front();
            q.pop();

            if(node[cur]) {
                res = true;
                break;
            }

            for(int nxt : g[cur]) {
                if(visit[nxt] == cnt)
                    continue;
                visit[nxt] = cnt;
                q.push(nxt);
            }
        }
        return res;
    };

    vector<char> dir(eg.size());
    auto bt = [&](auto&& self, int idx) -> bool {
        if(idx == eg.size()) {
            return cango();
        }

        int x = eg[idx].first;
        int y = eg[idx].second;
        // Vertical
        int x1 = x - 1;
        int y1 = y;
        int x2 = x + 1;
        int y2 = y;
        if(x1 >= 0 && x2 < n && d[x1][y1] != -1 && d[x2][y2] != -1) {
            int h1 = map[x1][y1] == '1' ? 1 : 0;
            int h2 = map[x2][y2] == '1' ? 1 : 0;
            if(h1 != h2) {
                if(h1 == 0) {
                    dir[idx] = 'S';
                } else {
                    dir[idx] = 'N';
                }
                g[d[x1][y1]].push_back(d[x2][y2]);
                g[d[x2][y2]].push_back(d[x1][y1]);

                bool r = self(self, idx + 1);
                if(r == true)
                    return true;
                g[d[x1][y1]].pop_back();
                g[d[x2][y2]].pop_back();
            }
        }

        // Horizontal
        x1 = x;
        y1 = y - 1;
        x2 = x;
        y2 = y + 1;
        if(y1 >= 0 && y2 < m && d[x1][y1] != -1 && d[x2][y2] != -1) {
            int h1 = map[x1][y1] == '1' ? 1 : 0;
            int h2 = map[x2][y2] == '1' ? 1 : 0;
            if(h1 != h2) {
                if(h1 == 0) {
                    dir[idx] = 'E';
                } else {
                    dir[idx] = 'W';
                }
                g[d[x1][y1]].push_back(d[x2][y2]);
                g[d[x2][y2]].push_back(d[x1][y1]);

                bool r = self(self, idx + 1);
                if(r == true)
                    return true;
                g[d[x1][y1]].pop_back();
                g[d[x2][y2]].pop_back();
            }
        }
        return false;
    };
    bool r = bt(bt, 0);
    if(r == true) {
        for(int i = 0; i < eg.size(); ++i) {
            int x = eg[i].first;
            int y = eg[i].second;
            map[x][y] = dir[i];
        }

        for(int i = 0; i < n; ++i) {
            cout << map[i] << "\n";
        }
    } else {
        cout << "-1\n";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
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
