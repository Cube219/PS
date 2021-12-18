#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
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
    vector<string> map(n);
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int j2 = m - j - 1;
            char ch = '.';
            if(map[i][j] != '.') ch = map[i][j];
            if(map[i][j2] != '.') ch = map[i][j2];
            cout << ch;
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
