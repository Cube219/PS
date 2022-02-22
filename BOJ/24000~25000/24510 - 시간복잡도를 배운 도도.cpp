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
    int c;
    cin >> c;
    int res = 0;
    auto has = [](const string& str, int idx) {
        if(str.substr(idx, 3) == "for") return true;
        if(str.substr(idx, 5) == "while") return true;
        return false;
    };
    for(int i = 0; i < c; ++i) {
        string str;
        cin >> str;
        int cur = 0;
        for(int j = 0; j < str.size(); ++j) {
            if(has(str, j)) cur++;
        }
        res = max(res, cur);
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
