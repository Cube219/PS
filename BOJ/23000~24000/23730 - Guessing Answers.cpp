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
    vector<int> ans(n), res(n);
    for(auto& v : ans) cin >> v;
    for(int i = 0; i < m; ++i) {
        int a;
        cin >> a;
        a--;
        res[a] = ans[a];
    }

    for(int i = 0; i < n; ++i) {
        if(res[i] != 0) continue;
        for(int j = 1; j <= 5; ++j) {
            if(i > 0 && res[i - 1] == j) continue;
            if(i < n - 1 && res[i + 1] == j) continue;
            if(ans[i] == j) continue;
            res[i] = j;
            break;
        }
    }

    for(int v : res) cout << v << " ";
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
