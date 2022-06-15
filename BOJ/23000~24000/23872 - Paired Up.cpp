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
    int t, n, k;
    cin >> t >> n >> k;
    struct Node
    {
        int x, y;
    };
    vector<Node> d(n);
    for(auto& v : d) cin >> v.x >> v.y;

    auto t1 = [k](vector<Node>& d) {
        int n = d.size();
        if(n & 1) {
            int mn = INF;
            for(int i = 0; i < n; ++i) {
                if((i & 1) == 0 || d[i + 1].x - d[i - 1].x <= k) mn = min(mn, d[i].y);
            }
            return mn;
        } else {
            return 0;
        }
    };

    auto t2 = [k](vector<Node>& d) {
        int n = d.size();
        vector<int> idx(n);
        int l = 0;
        for(int i = 0; i < n; ++i) {
            while(d[i].x - d[l].x > k) l++;
            idx[i] = l - 1;
        }

        struct DPNode
        {
            int even, odd;
        };
        vector<DPNode> dp(n + 1);
        dp[0] = { 0, -INF };
        for(int i = 1; i <= n; ++i) {
            // 안 지우는 경우
            dp[i] = dp[i - 1];

            // 지우는 경우
            int lidx = idx[i - 1] + 1;
            if(i & 1) {
                // 앞에 even개
                dp[i].odd = max(dp[i].odd, dp[lidx].even + d[i - 1].y);
            } else {
                // 앞에 odd개
                dp[i].even = max(dp[i].even, dp[lidx].odd + d[i - 1].y);
            }

            if(i == 1 || i == n || d[i + 1 - 1].x - d[i - 1 - 1].x <= k) {
                dp[i].even = max(dp[i].even, dp[lidx].odd + d[i - 1].y);
                dp[i].odd = max(dp[i].odd, dp[lidx].even + d[i - 1].y);
            }
        }

        if(n & 1) return dp[n].odd;
        else return dp[n].even;
    };

    int res = 0;
    vector<Node> cur;
    for(auto& v : d) {
        if(cur.size() == 0 || v.x - cur.back().x <= k) cur.push_back(v);
        else {
            if(t == 1) res += t1(cur);
            else res += t2(cur);
            cur.clear();
            cur.push_back(v);
        }
    }
    if(t == 1) res += t1(cur);
    else res += t2(cur);
    cur.clear();

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
