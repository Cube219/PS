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
    sort(d.begin(), d.end());

    bool same = false;
    for(int i = 0; i < n - 1; ++i) {
        if(d[i] == d[i + 1]) {
            same = true;
            break;
        }
    }

    int zero = 0;
    for(int i = 0; i < n; ++i) {
        if(d[i] == 0) zero++;
    }

    if(zero > 0) {
        cout << n - zero;
    } else {
        if(same) cout << n;
        else cout << n + 1;
    }
    cout << "\n";
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
