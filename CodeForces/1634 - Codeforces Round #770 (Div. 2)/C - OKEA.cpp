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
    int n, k;
    cin >> n >> k;
    if(k == 1) {
        cout << "YES\n";
        for(int i = 1; i <= n; ++i) {
            cout << i << "\n";
        }
    } else {
        if(n & 1) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for(int i = 1; i <= n; ++i) {
                int cur = i;
                for(int j = 0; j < k; ++j) {
                    cout << cur << " ";
                    cur += n;
                }
                cout << "\n";
            }
        }
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
