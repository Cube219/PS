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
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    if(d[n - 1] < 0) {
        cout << "-1";
        return;
    }

    vector<int> res(n);
    int cur = n;
    for(int i = 0; i < n; ++i) {
        if(d[i] < 0) continue;
        res[i] = cur--;
    }
    for(int i = n - 1; i >= 0; --i) {
        if(d[i] > 0) continue;
        res[i] = cur--;
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
