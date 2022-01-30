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

    vector<int> res;

    int n2 = 1;
    while(n2 * 2 < n) n2 *= 2;

    int cur = n - 1;
    while(cur >= n2) {
        res.push_back(cur);
        cur--;
    }
    res.push_back(0);
    while(cur > 0) {
        res.push_back(cur);
        cur--;
    }

    for(int v : res) cout << v << " ";
    cout << "\n";

    // int mx = 0;
    // for(int i = 0; i < n - 1; ++i) {
    //     mx = max(mx, res[i] ^ res[i + 1]);
    // }
    // cout << "mx: " << mx << "\n";
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
