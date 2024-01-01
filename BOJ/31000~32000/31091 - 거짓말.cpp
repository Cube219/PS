#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
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
    vector<int> d(n + 1, 0), d2(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        if (k > 0) {
            d[k]++;
        } else {
            d2[-k]++;
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        d[i] += d[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        d2[i] += d2[i + 1];
    }
    for (int i = 0; i < n + 1; ++i) {
        d[i] += d2[i];
    }

    vector<int> res;
    for (int i = 0; i < n + 1; ++i) {
        if (d[i] == n - i) res.push_back(i);
    }

    cout << res.size() << "\n";
    for (int v : res) cout << v << " ";
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
    for (int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
