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
    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;

    vector<vector<int>> num(2, vector<int>(2, 0));
    for(int i = 0; i < n; ++i) {
        num[s1[i] - '0'][s2[i] - '0']++;
    }

    int res = INF;
    if((num[0][0] + num[1][1]) % 2 == 1) {
        if(num[0][0] + 1 == num[1][1]) res = min(res, num[0][0] + num[1][1]);
    }
    if((num[0][1] + num[1][0]) % 2 == 0) {
        if(num[0][1] == num[1][0]) res = min(res, num[0][1] + num[1][0]);
    }

    if(res == INF) res = -1;
    if(s1 == s2) res = 0;

    cout << res << "\n";
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
