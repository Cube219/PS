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

    if(map[0][0] == 1) {
        cout << "-1\n";
        return;
    }

    struct Res
    {
        int x1, y1, x2, y2;
    };
    vector<Res> res;

    for(int i = n - 1; i >= 0; --i) {
        for(int j = m - 1; j >= 1; --j) {
            if(map[i][j] == 1) {
                res.push_back({ i, j - 1, i, j });
            }
        }
    }
    for(int i = n - 1; i >= 1; --i) {
        if(map[i][0] == 1) {
            res.push_back({ i - 1, 0, i, 0 });
        }
    }

    cout << res.size() << "\n";
    for(auto [x1, y1, x2, y2] : res) {
        x1++; x2++; y1++; y2++;
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
