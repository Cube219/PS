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

int d[51][51][51][51];

void solve(int n, int m)
{
    vector<string> map(n);
    for(auto& v : map) cin >> v;

    vector<vector<int>> pos(n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == '#') {
                d[i][j][i][j] = -INF;
            } else {
                d[i][j][i][j] = 0;
                if(map[i][j] != '.') pos[i].push_back(j);
            }
        }
    }

    constexpr int gap = 'a' - 'A';
    auto isPair = [&](char src, char dst) {
        if(src - gap == dst && dst != '.') return true;
        return false;
    };
    for(int xsz = 1; xsz <= n; ++xsz) {
        for(int ysz = 1; ysz <= m; ++ysz) {
            if(xsz == 1 && ysz == 1) continue;

            for(int sx = 0; sx < n - xsz + 1; ++sx) {
                for(int sy = 0; sy < m - ysz + 1; ++sy) {
                    int ex = sx + xsz - 1;
                    int ey = sy + ysz - 1;

                    if(map[sx][sy] == '#' || map[ex][ey] == '#') {
                        d[sx][sy][ex][ey] = -INF;
                        continue;
                    }

                    int res = -INF;
                    if(xsz > 1) {
                        res = max(res, d[sx + 1][sy][ex][ey]);
                        res = max(res, d[sx][sy][ex - 1][ey]);
                    }
                    if(ysz > 1) {
                        res = max(res, d[sx][sy + 1][ex][ey]);
                        res = max(res, d[sx][sy][ex][ey - 1]);
                    }

                    if(isPair(map[sx][sy], map[ex][ey])){
                        int v = -INF;
                        int sx2, sy2, ex2, ey2;

                        sx2 = sx; sy2 = sy + 1;
                        ex2 = ex - 1; ey2 = ey;
                        if(sx2 <= ex2 && sy2 <= ey2) v = max(v, d[sx2][sy2][ex2][ey2]);
                        ex2 = ex; ey2 = ey - 1;
                        if(sx2 <= ex2 && sy2 <= ey2) v = max(v, d[sx2][sy2][ex2][ey2]);

                        sx2 = sx + 1; sy2 = sy;
                        ex2 = ex - 1; ey2 = ey;
                        if(sx2 <= ex2 && sy2 <= ey2) v = max(v, d[sx2][sy2][ex2][ey2]);
                        ex2 = ex; ey2 = ey - 1;
                        if(sx2 <= ex2 && sy2 <= ey2) v = max(v, d[sx2][sy2][ex2][ey2]);

                        res = max(res, v + 1);
                        if(sx == ex && sy + 1 == ey) res = max(res, 1);
                        if(sy == ey && sx + 1 == ex) res = max(res, 1);
                    }

                    if('a' <= map[sx][sy] && map[sx][sy] <= 'z' &&
                        'A' <= map[ex][ey] && map[ex][ey] <= 'Z') {
                        for(int mx = sx; mx <= ex; ++mx) {
                            for(int my : pos[mx]) {
                                if(my < sy) continue;
                                if(my > ey) break;

                                if(mx < ex) {
                                    int v = d[mx + 1][my][ex][ey];
                                    if(isPair(map[mx][my], map[mx + 1][my])) v++;
                                    res = max(res, d[sx][sy][mx][my] + v);
                                }
                                if(my < ey) {
                                    int v = d[mx][my + 1][ex][ey];
                                    if(isPair(map[mx][my], map[mx][my + 1])) v++;
                                    res = max(res, d[sx][sy][mx][my] + v);
                                }
                            }
                        }
                    }

                    d[sx][sy][ex][ey] = res;
                }
            }
        }
    }

    if(d[0][0][n - 1][m - 1] < 0) d[0][0][n - 1][m - 1] = -1;
    cout << d[0][0][n - 1][m - 1] << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(1) {
        int n, m;
        cin >> n >> m;
        if(n == 0 && m == 0) break;
        solve(n, m);
    }

    return 0;
}
