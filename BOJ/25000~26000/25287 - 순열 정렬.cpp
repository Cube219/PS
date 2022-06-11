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
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    d[0] = min(d[0], n - d[0] + 1);

    for(int i = 1; i < n; ++i) {
        int a = d[i];
        int b = n - a + 1;
        if(a > b) swap(a, b);
        if(d[i - 1] <= a) d[i] = a;
        else d[i] = b;
    }

    bool res = true;
    for(int i = 0; i < n - 1; ++i) {
        if(d[i] > d[i + 1]) {
            res = false;
            break;
        }
    }

    if(res) cout << "YES\n";
    else cout << "NO\n";
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
