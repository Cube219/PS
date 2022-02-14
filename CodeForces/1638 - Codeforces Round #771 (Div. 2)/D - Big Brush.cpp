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
    vector<vector<int>> map(n, vector<int>(m));
    for(auto& v1 : map) {
        for(auto& v2 : v1) cin >> v2;
    }

    vector<vector<int>> cnt(n - 1, vector<int>(m - 1, 1));
    for(int i = 0; i < n - 1; ++i) {
        for(int j = 0; j < m - 1; ++j) {
            if(map[i][j] == map[i + 1][j]) cnt[i][j]++;
            if(map[i][j] == map[i][j + 1]) cnt[i][j]++;
            if(map[i][j] == map[i + 1][j + 1]) cnt[i][j]++;
        }
    }

    struct Node
    {
        int x, y, col;
        bool operator<(const Node& rhs) const
        {
            return col < rhs.col;
        }
    };
    vector<Node> res;
    queue<Node> q;

    vector<vector<char>> comp(n, vector<char>(m, false));
    auto recal = [&](int x, int y) {
        if(comp[x][y]) return;

        int col = -1;
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                if(map[x + i][y + j] == 0) continue;
                if(col != -1 && col != map[x + i][y + j]) return;
                col = map[x + i][y + j];
            }
        }
        q.push({ x, y, col });
    };
    for(int i = 0; i < n - 1; ++i) {
        for(int j = 0; j < m - 1; ++j) {
            recal(i, j);
        }
    }

    while(q.empty() == false) {
        auto [x, y, col] = q.front();
        q.pop();

        if(comp[x][y]) continue;

        comp[x][y] = true;
        res.push_back({ x, y, col });

        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                map[x + i][y + j] = 0;
            }
        }

        for(int i = 0; i < 2; ++i) {
            int nx = x + i;
            if(nx >= n - 1) continue;
            for(int j = 0; j < 2; ++j) {
                int ny = y + j;
                if(ny >= m - 1) continue;

                if(nx > 0) recal(nx - 1, ny);
                if(ny > 0) recal(nx, ny - 1);
                if(nx > 0 && ny > 0) recal(nx - 1, ny - 1);
                recal(nx, ny);
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] != 0) {
                res.clear();
            }
        }
    }

    if(res.size() == 0) cout << "-1";
    else {
        cout << res.size() << "\n";
        for(int i = res.size() - 1; i >= 0; --i) {
            cout << res[i].x + 1 << " " << res[i].y + 1 << " " << res[i].col << "\n";
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
