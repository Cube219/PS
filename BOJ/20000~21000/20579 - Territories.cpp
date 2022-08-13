#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int num, n, m;
    cin >> num >> m >> n;
    struct Node
    {
        int x1, y1, x2, y2, c;
    };
    vector<Node> d(num);
    vector<vector<int>> map(n, vector<int>(m, 0));
    auto c0 = map; // 0,0에 두는 개수
    auto c1 = map; // 0,y-1에 두는 개수
    auto c2 = map; // x-1,0에 두는 개수
    auto c3 = map; // x-1,y-1에 두는 개수

    auto update = [&](int x, int y, Node v, int dv) {
        map[x][y] += dv;
        if(v.x1 > 0 || v.y1 > 0) c0[x][y] += dv;
        if(v.x1 > 0 || v.y2 < m - 1) c1[x][y] += dv;
        if(v.x2 < n - 1 || v.y1 > 0) c2[x][y] += dv;
        if(v.x2 < n - 1 || v.y2 < m - 1) c3[x][y] += dv;
    };

    ll sumc = 0;
    for(auto& v : d) {
        cin >> v.y1 >> v.x1 >> v.y2 >> v.x2 >> v.c;
        v.x1--; v.y1--; v.x2--; v.y2--;

        update(v.x1, v.y1, v, v.c);
        if(v.x2 < n - 1) update(v.x2 + 1, v.y1, v, -v.c);
        if(v.y2 < m - 1) update(v.x1, v.y2 + 1, v, -v.c);
        if(v.x2 < n - 1 && v.y2 < m - 1) update(v.x2 + 1, v.y2 + 1, v, v.c);

        sumc += v.c;
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 1; j < m; ++j) {
            map[i][j] += map[i][j - 1];
            c0[i][j] += c0[i][j - 1];
            c1[i][j] += c1[i][j - 1];
            c2[i][j] += c2[i][j - 1];
            c3[i][j] += c3[i][j - 1];
        }
    }
    for(int j = 0; j < m; ++j) {
        for(int i = 1; i < n; ++i) {
            map[i][j] += map[i - 1][j];
            c0[i][j] += c0[i - 1][j];
            c1[i][j] += c1[i - 1][j];
            c2[i][j] += c2[i - 1][j];
            c3[i][j] += c3[i - 1][j];
        }
    }

    ll res = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ll v1 = sumc - map[i][j];
            ll remain = map[i][j];

            ll v2 = c0[i][j];
            ll v3 = remain - v2;
            auto cal = [&]() {
                return v1 * (v1 - 1) / 2 + v2 * (v2 - 1) / 2 + v3 * (v3 - 1) / 2;
            };
            res = max(res, cal());

            v2 = c1[i][j];
            v3 = remain - v2;
            res = max(res, cal());

            v2 = c2[i][j];
            v3 = remain - v2;
            res = max(res, cal());

            v2 = c3[i][j];
            v3 = remain - v2;
            res = max(res, cal());
        }
    }

    cout << res;
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
