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
    struct Node
    {
        int t, x;
        ll a;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.t >> v.x >> v.a;

    sort(d.begin(), d.end(), [](const auto& l, const auto& r) {
        return l.t > r.t;
    });
    vector<ll> dp(5, -LNF), ndp(5, -LNF);
    dp[0] = 0;
    vector<int> dy = { -1, 0, 1 };
    for(int i = 1; i <= 100000; ++i) {
        vector<ll> score(5, 0);
        fill(ndp.begin(), ndp.end(), -LNF);

        while(!d.empty() && d.back().t == i) {
            score[d.back().x] += d.back().a;
            d.pop_back();
        }

        for(int j = 0; j < 5; ++j) {
            for(int k = 0; k < 3; ++k) {
                int nj = j + dy[k];
                if(nj < 0 || nj >= 5) continue;
                ndp[j] = max(ndp[j], dp[nj] + score[j]);
            }
        }

        swap(dp, ndp);
    }

    ll res = -LNF;
    for(int i = 0; i < 5; ++i) {
        res = max(res, dp[i]);
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
