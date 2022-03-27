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

    for(int i = 0; i < n; ++i) {
        if(d[i] != 0) continue;

        vector<char> canUse(4, true);
        if(i > 0) canUse[d[i - 1]] = false;
        if(i < n - 1) canUse[d[i + 1]] = false;
        for(int j = 1; j <= 3; ++j) {
            if(canUse[j]) {
                d[i] = j;
                break;
            }
        }
    }

    bool res = true;
    for(int i = 0; i < n; ++i) {
        if(i > 0 && d[i-1] == d[i]) {
            res = false;
            break;
        }
        if(i < n - 1 && d[i] == d[i + 1]) {
            res = false;
            break;
        }
    }

    if(res) {
        for(int v : d) cout << v << " ";
    } else {
        cout << "-1";
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
