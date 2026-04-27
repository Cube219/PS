#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#undef _LIBCPP_ENABLE_ASSERTIONS


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
    int n, tMax;
    cin >> n >> tMax;
    struct Node
    {
        int t, a, b;
        bool operator<(const Node& rhs) const { return t < rhs.t; }
    };
    vector<Node> d(n);
    for (auto& v : d) cin >> v.t >> v.a >> v.b;

    int res = 0;

    for (auto [t, a, b] : d) {
        if (tMax >= t) {
            res = max(res, a + b);
        }
    }

    vector<Node> rhs = d;
    sort(rhs.begin(), rhs.end());
    vector<int> mx(n);
    for(int i = 0; i < n; ++i) {
        mx[i] = rhs[i].b;
        if (i > 0) {
            mx[i] = max(mx[i], mx[i-1]);
        }
    }

    for (auto [t, a, b] : d) {
        int remainT = tMax - t;
        auto it = upper_bound(rhs.begin(), rhs.end(), Node{remainT, 0, 0});
        if (it != rhs.begin()) {
            --it;
            int idx = it - rhs.begin();
            res = max(res, a + mx[idx]);
        }
    }

    cout<<res;
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
