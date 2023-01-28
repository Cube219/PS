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

    bool res = true;
    int curY = 1;
    for(int i = 0; i < n - 1; ++i) {
        int num;
        cin >> num;

        if(num == 0) continue;
        else if(num == 1) {
            int pos; char dir;
            cin >> pos >> dir;
            if(dir == 'L') {
                curY = max(curY, pos + 1);
                if(curY > m) res = false;
            } else {
                if(curY >= pos) res = false;
            }
        } else {
            int p1, p2; char d1, d2;
            cin >> p1 >> d1 >> p2 >> d2;
            if(d1 == 'L') {
                if(d2 == 'L') {
                    // LL
                    curY = max(curY, p2 + 1);
                    if(curY > m) res = false;
                } else {
                    // LR
                    curY = max(curY, p1 + 1);
                    if(curY >= p2) res = false;
                }
            } else {
                if(d2 == 'L') {
                    // RL
                    if(p1 <= curY) curY = max(curY, p2 + 1);
                    if(curY > m) res = false;
                } else {
                    // RR
                    if(curY >= p1) res = false;
                }
            }
        }
    }

    if(res) cout << "YES";
    else cout << "NO";
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
