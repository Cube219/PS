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
    string str;
    cin >> str;
    int n = str.size();

    bool res = true;
    int gap = str[1] - str[0];
    for(int i = 2; i < n; ++i) {
        int cur = str[i] - str[i - 1];
        if(gap * cur == 0) {
            res = false;
            break;
        } else if(gap * cur < 0) {
            gap = cur;
        } else if(gap != cur) {
            res = false;
            break;
        }
    }

    if(str[1] - str[0] <= 0) res = false;
    if(str[n - 1] - str[n - 2] >= 0) res = false;

    if(res == false) cout << "NON ALPSOO";
    else cout << "ALPSOO";
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
