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

struct Node
{
    int x, y, w, h;
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> map(n);
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }

    vector<vector<int>> sum(n, vector<int>(m, 0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'X') sum[i][j] = 1;
            if(i > 0) sum[i][j] += sum[i - 1][j];
            if(j > 0) sum[i][j] += sum[i][j - 1];
            if(i > 0 && j > 0) sum[i][j] -= sum[i - 1][j - 1];
        }
    }
    auto ck = [&](int x1, int y1, int x2, int y2) {
        if(x1 < 0 || y1 < 0 || x1 >= n || y1 >= m) return false;
        if(x2 < 0 || y2 < 0 || x2 >= n || y2 >= m) return false;

        int res = sum[x2][y2];
        if(x1 > 0) res -= sum[x1 - 1][y2];
        if(y1 > 0) res -= sum[x2][y1 - 1];
        if(x1 > 0 && y1 > 0) res += sum[x1 - 1][y1 - 1];

        return res == 0;
    };

    // [x][y][wid][hei]
    // 0: 방문X / 1: 가능 / 2: 불가능
    vector<vector<vector<vector<char>>>> d;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        d[i].resize(m);
        for(int j = 0; j < m; ++j) {
            d[i][j].resize(m + 1);
            for(int k = 0; k <= m; ++k) {
                d[i][j][k].resize(n + 1, 0);
            }
        }
    }

    queue<Node> q;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'A') {
                q.push({ i, j, 1, 1 });
                d[i][j][1][1] = 1;
            }
        }
    }
    auto ck_node = [&](Node nxt) {
        int x2 = nxt.x + nxt.h - 1;
        int y2 = nxt.y + nxt.w - 1;
        return ck(nxt.x, nxt.y, x2, y2);
    };
    vector<int> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };
    while(!q.empty()){
        auto cur = q.front();
        q.pop();

        // 오른쪽
        Node nxt = cur;
        nxt.w++;
        if(ck_node(nxt)) {
            for(int i = 0; i < 4; ++i) {
                Node nxt2 = nxt;
                nxt2.x += dx[i];
                nxt2.y += dy[i];
                if(ck_node(nxt2) && d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] == 0) {
                    d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] = 1;
                    q.push({ nxt2.x, nxt2.y, nxt2.w, nxt2.h });
                }
            }
        }

        // 왼쪽
        nxt = cur;
        nxt.y--;
        nxt.w++;
        if(ck_node(nxt)) {
            for(int i = 0; i < 4; ++i) {
                Node nxt2 = nxt;
                nxt2.x += dx[i];
                nxt2.y += dy[i];
                if(ck_node(nxt2) && d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] == 0) {
                    d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] = 1;
                    q.push({ nxt2.x, nxt2.y, nxt2.w, nxt2.h });
                }
            }
        }

        // 위
        nxt = cur;
        nxt.x--;
        nxt.h++;
        if(ck_node(nxt)) {
            for(int i = 0; i < 4; ++i) {
                Node nxt2 = nxt;
                nxt2.x += dx[i];
                nxt2.y += dy[i];
                if(ck_node(nxt2) && d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] == 0) {
                    d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] = 1;
                    q.push({ nxt2.x, nxt2.y, nxt2.w, nxt2.h });
                }
            }
        }

        // 아래
        nxt = cur;
        nxt.h++;
        if(ck_node(nxt)) {
            for(int i = 0; i < 4; ++i) {
                Node nxt2 = nxt;
                nxt2.x += dx[i];
                nxt2.y += dy[i];
                if(ck_node(nxt2) && d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] == 0) {
                    d[nxt2.x][nxt2.y][nxt2.w][nxt2.h] = 1;
                    q.push({ nxt2.x, nxt2.y, nxt2.w, nxt2.h });
                }
            }
        }
    }

    sum.clear();
    sum.resize(n + 1, vector<int>(m + 1, 0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k <= m; ++k) {
                for(int z = 0; z <= n; ++z) {
                    if(d[i][j][k][z] == 0) continue;
                    sum[i][j]++;
                    sum[i][j + k]--;
                    sum[i + z][j]--;
                    sum[i + z][j + k]++;
                }
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(j > 0) sum[i][j] += sum[i][j - 1];
        }
    }
    for(int j = 0; j < m; ++j) {
        for(int i = 0; i < n; ++i) {
            if(i > 0) sum[i][j] += sum[i - 1][j];
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(sum[i][j] > 0) cout << "Y";
            else cout << "N";
        }
        cout << "\n";
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
