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
    constexpr int MX = 1'000'000;

    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    vector<vector<int>> res(MX + 1);

    for(int v : d) {
        for(int i = 1; i * i <= v; ++i) {
            if(v % i != 0) continue;
            res[v / i].push_back(i);
            if(i != v / i) res[i].push_back(v / i);
        }

    }
    vector<char> has(MX + 1, false);
    for(int i = 1; i <= MX; ++i) {
        if(res[i].size() == 0) continue;

        int g = res[i][0];
        for(int v : res[i]) g = gcd(g, v);
        if(g == 1) has[i] = true;
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int v;
        cin >> v;
        if(has[v] == false) cout << "-1\n";
        else cout << res[v].size() << "\n";
    }
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
