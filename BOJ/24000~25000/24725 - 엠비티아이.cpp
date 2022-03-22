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
    vector<string> d(n);
    for(auto& v : d) cin >> v;

    vector<vector<char>> tb = { { 'E', 'I' }, { 'N', 'S' }, { 'F', 'T' }, { 'P', 'J' } };
    vector<int> dx = { 1, 0, -1, 0, 1, -1, 1, -1 };
    vector<int> dy = { 0, 1, 0, -1, 1, -1, -1, 1 };

    int res = 0;

    auto ck = [&](int x, int y) {
        for(int i = 0; i < 8; ++i) {
            int nx = x + dx[i] * 3;
            int ny = y + dy[i] * 3;
            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

            bool f = true;
            for(int j = 0; j < 4; ++j) {
                nx = x + dx[i] * j;
                ny = y + dy[i] * j;
                if(d[nx][ny] != tb[j][0] && d[nx][ny] != tb[j][1]) {
                    f = false;
                    break;
                }
            }
            if(f) res++;
        }
    };
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ck(i, j);
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
