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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> map(n, vector<int>(m));
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < m; ++j) {
            map[i][j] = str[j] - '0';
        }
    }

    auto ck = [&](int x1, int y1, int x2, int y2) {
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        bool pos = true;
        for(int i = x1; i <= x2; ++i) {
            for(int j = y1; j <= y2; ++j) {
                if(map[i][j] != 1) {
                    pos = false;
                    break;
                }
            }
        }

        if(pos == false) {
            for(int i = x1; i <= x2; ++i) {
                for(int j = y1; j <= y2; ++j) {
                    if(map[i][j] != 0) {
                        return -1;
                    }
                }
            }
            return 0;
        }

        for(int i = x1; i <= x2; ++i) {
            for(int j = y1; j <= y2; ++j) {
                map[i][j] = 2;
            }
        }
        return 1;
    };

    auto process = [&](int x, int y) -> bool {
        int x1 = x, x2 = x, y1 = y, y2 = y;
        map[x][y] = 2;
        // left
        while(y1 > 0) {
            int r = ck(x1, y1 - 1, x2, y1 - 1);
            if(r == -1) return false;
            else if(r == 0) break;
            y1--;
        }

        // right
        while(y2 < m - 1) {
            int r = ck(x1, y2 + 1, x2, y2 + 1);
            if(r == -1) return false;
            else if(r == 0) break;
            y2++;
        }

        // up
        while(x1 > 0) {
            int r = ck(x1 - 1, y1, x1 - 1, y2);
            if(r == -1) return false;
            else if(r == 0) break;
            x1--;
        }

        // down
        while(x2 < n - 1) {
            int r = ck(x2 + 1, y1, x2 + 1, y2);
            if(r == -1) return false;
            else if(r == 0) break;
            x2++;
        }

        return true;
    };

    bool res = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 1) {
                res = process(i, j);
                if(res == false) break;
            }
        }
        if(res == false) break;
    }

    if(res) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
