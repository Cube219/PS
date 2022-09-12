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
    int n;
    cin >> n;
    struct Point { ll x, y; };
    Point st, ed;
    cin >> st.x >> st.y >> ed.x >> ed.y;

    int res = -1;
    ll mn = LNF;
    for(int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        Point cur = st;
        ll dis = 0;
        for(int j = 0; j < m; ++j) {
            Point v;
            cin >> v.x >> v.y;
            dis += abs(cur.x - v.x) + abs(cur.y - v.y);
            cur = v;
        }
        dis += abs(cur.x - ed.x) + abs(cur.y - ed.y);
        if(mn > dis) {
            mn = dis;
            res = i;
        }
    }

    cout << res + 1;
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
