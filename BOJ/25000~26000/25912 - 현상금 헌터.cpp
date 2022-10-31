#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
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
    int n, t;
    cin >> n >> t;
    struct Node { int x, y, b, dx, dy; };
    vector<Node> d(n);
    for(auto& v : d) {
        int dir;
        cin >> v.x >> v.y >> v.b >> dir;
        v.x *= 2;
        v.y *= 2;

        v.dx = v.dy = 0;
        if(dir == 0) v.dx = 1;
        else if(dir == 1) v.dy = -1;
        else if(dir == 2) v.dx = -1;
        else v.dy = 1;
    }

    auto tryCatch = [&](int x, int y, int idx, int t) {
        auto [cx, cy, _, dx, dy] = d[idx];
        if(dx != 0) {
            // Horizontal
            int mvY = abs(cy - y);
            t += mvY;
            cx += dx * t;

            if((dx > 0 && cx <= x) || (dx < 0 && x <= cx)) {
                assert((cx + x) % 2 == 0);
                int midX = (cx + x) / 2;
                int mvX = abs(x - midX);
                return t + mvX + 2;
            }
        } else {
            // Vertical
            int mvX = abs(cx - x);
            t += mvX;
            cy += dy * t;

            if((dy > 0 && cy <= y) || (dy < 0 && y <= cy)) {
                assert((cy + y) % 2 == 0);
                int midY = (cy + y) / 2;
                int mvY = abs(y - midY);
                return t + mvY + 2;
            }
        }
        return -1;
    };

    vector<vector<int>> dp(t * 2 + 1, vector<int>(n, -1));
    for(int i = 0; i < n; ++i) {
        int res = tryCatch(0, 0, i, 0);
        if(res >= 0 && res <= t * 2) {
            dp[res][i] = d[i].b;
        }
    }

    int res = 0;
    for(int i = 0; i <= t * 2; ++i) {
        for(int j = 0; j < n; ++j) {
            if(dp[i][j] == -1) continue;

            res = max(res, dp[i][j]);

            int cx = d[j].x + d[j].dx * (i - 2);
            int cy = d[j].y + d[j].dy * (i - 2);

            for(int k = 0; k < n; ++k) {
                int nxtT = tryCatch(cx, cy, k, i);
                if(0 <= nxtT && nxtT <= t * 2) {
                    dp[nxtT][k] = max(dp[nxtT][k], dp[i][j] + d[k].b);
                }
            }
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
