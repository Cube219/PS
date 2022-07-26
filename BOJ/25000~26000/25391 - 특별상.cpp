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
    int n, m, k;
    cin >> n >> m >> k;
    struct Node
    {
        int a, b;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.a >> v.b;

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.b < r.b;
    });

    ll res = 0;
    for(int i = 0; i < k; ++i) {
        res += d.back().a;
        d.pop_back();
    }

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.a < r.a;
    });
    for(int i = 0; i < m; ++i) {
        res += d.back().a;
        d.pop_back();
    }

    cout << res;
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
