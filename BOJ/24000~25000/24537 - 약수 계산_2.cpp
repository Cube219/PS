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
    vector<int> d(MX + 1, 0);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        d[a]++;
    }

    int q;
    cin >> q;
    vector<int> rec(MX + 1, -2);
    for(int i = 0; i < q; ++i) {
        int v;
        cin >> v;

        if(rec[v] != -2) {
            cout << rec[v] << "\n";
            continue;
        }

        int res = 0;
        int g = -1;
        for(int j = v; j <= MX; j += v) {
            if(d[j] == 0) continue;
            if(g == -1) g = j;
            else g = gcd(g, j);
            res += d[j];

            if(g < v) break;
        }

        if(g == -1 || g != v) res = -1;
        cout << res << "\n";
        rec[v] = res;
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
