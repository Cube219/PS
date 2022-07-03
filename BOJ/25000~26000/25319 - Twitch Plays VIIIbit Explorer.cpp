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
    int n, m, l;
    cin >> n >> m >> l;
    vector<string> map(n);
    for(auto& v : map) cin >> v;
    string str;
    cin >> str;

    struct Point
    {
        int x, y;
    };
    vector<vector<Point>> list(26);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            char ch = map[i][j];
            list[ch - 'a'].push_back({ i, j });
        }
    }

    vector<int> num(26, 0);
    for(char ch : str) num[ch - 'a']++;

    int c = INF;
    for(int i = 0; i < 26; ++i) {
        if(num[i] == 0) continue;
        c = min(c, (int)list[i].size() / num[i]);
    }

    string res;
    Point cur = { 0, 0 };
    auto move = [&](int x, int y) {
        if(cur.x < x) {
            for(int i = 0; i < x - cur.x; ++i) {
                res.push_back('D');
            }
        } else {
            for(int i = 0; i < cur.x - x; ++i) {
                res.push_back('U');
            }
        }
        if(cur.y < y) {
            for(int i = 0; i < y - cur.y; ++i) {
                res.push_back('R');
            }
        } else {
            for(int i = 0; i < cur.y - y; ++i) {
                res.push_back('L');
            }
        }
        cur = { x, y };
    };
    for(int cc = 0; cc < c; ++cc) {
        for(char ch : str) {
            auto [x, y] = list[ch - 'a'].back();
            list[ch - 'a'].pop_back();

            move(x, y);
            res.push_back('P');
        }
    }
    move(n - 1, m - 1);

    cout << c << " " << res.size() << "\n";
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
