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
    int y, m;
    cin >> y >> m;
    bool yy = false;
    if(y % 4 == 0) {
        if(y % 100 == 0) {
            if(y % 400 == 0) yy = true;
        } else {
            yy = true;
        }
    }

    int d = 0;
    m--;
    if(m == 0) {
        m = 12;
        y--;
    }

    switch(m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            d = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            d = 30;
            break;
        case 2:
            if(yy) d = 29;
            else d = 28;
            break;
    }

    cout << y << " " << m << " " << d << "\n";
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
