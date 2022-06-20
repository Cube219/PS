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
    vector<vector<int>> map(n + 2, vector<int>(m + 2));
    for(auto& v : map) for(auto& v2 : v) cin >> v2;

    n++; m++;

    vector<vector<int>> res(n + 1, vector<int>(m + 1, -1));

    auto ck = [&](int x, int y) {
        int cnt = 0;
        for(int i = -1; i <= 1; ++i) {
            for(int j = -1; j <= 1; ++j) {
                int nx = x - i;
                int ny = y - j;
                if(nx < 0 || ny < 0 || nx >= n + 1 || ny >= m + 1) continue;
                if(res[nx][ny] == 1) cnt++;
            }
        }
        return cnt;
    };

    bool pos = true;
    for(int i = 0; i < n - 1; ++i) {
        for(int j = 0; j < m - 1; ++j) {
            int cnt = ck(i, j);

            if(map[i][j] == cnt) {
                res[i + 1][j + 1] = 0;
            } else if(map[i][j] - 1 == cnt) {
                res[i + 1][j + 1] = 1;
            } else {
                pos = false;
            }
        }
    }

    for(int i = 0; i < n + 1; ++i) {
        for(int j = 0; j < m + 1; ++j) {
            if(ck(i, j) != map[i][j]) pos = false;
        }
    }

    if(!pos) cout << "impossible";
    else {
        for(int i = 1; i < n; ++i) {
            for(int j = 1; j < m; ++j) {
                if(res[i][j] == 0) cout << ".";
                else cout << "X";
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
