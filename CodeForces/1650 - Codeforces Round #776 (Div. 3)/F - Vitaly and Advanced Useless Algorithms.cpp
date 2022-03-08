#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    struct Node
    {
        ll t;
        int p, idx;
    };
    vector<int> pp(m);
    vector<vector<Node>> d(n);
    for(int i = 0; i < m; ++i) {
        int e, t, p;
        cin >> e >> t >> p;
        d[e - 1].push_back({ t, p, i });
        pp[i] = p;
    }

    vector<int> res;
    ll curTime = 0;
    for(int i = 0; i < n; ++i) {
        if(d[i].size() == 0) {
            curTime = -1;
            break;
        }
        vector<vector<ll>> dp(d[i].size(), vector<ll>(201, LNF));
        vector<vector<int>> use(d[i].size(), vector<int>(201, 0));
        dp[0][0] = 0;
        dp[0][d[i][0].p] = d[i][0].t;
        use[0][d[i][0].p] = 1;

        for(int j = 1; j < d[i].size(); ++j) {
            auto [t, p, idx] = d[i][j];

            dp[j] = dp[j - 1];
            for(int k = p; k < 201; ++k) {
                if(dp[j][k] <= dp[j - 1][k - p] + t) continue;
                dp[j][k] = dp[j - 1][k - p] + t;
                use[j][k] = 1;
            }
        }

        ll mn = LNF;
        int curp = -1;
        for(int j = 100; j <= 200; ++j) {
            if(mn > dp[d[i].size() - 1][j]) {
                mn = dp[d[i].size() - 1][j];
                curp = j;
            }
        }

        curTime += mn;
        if(curTime > a[i]) {
            curTime = -1;
            break;
        }

        for(int j = d[i].size() - 1; j >= 0; --j) {
            if(use[j][curp] == 0) continue;
            res.push_back(d[i][j].idx + 1);
            curp -= d[i][j].p;
        }
    }

    if(curTime < 0) {
        cout << "-1\n";
    } else {
        cout << res.size() << "\n";
        for(int v : res) cout << v << " ";
        cout << "\n";
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
