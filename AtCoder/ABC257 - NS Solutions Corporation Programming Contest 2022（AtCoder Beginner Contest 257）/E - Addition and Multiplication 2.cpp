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
    vector<char> has(n + 1, false);
    vector<int> c(10);
    for(int i = 1; i <= 9; ++i) {
        cin >> c[i];
    }

    for(int i = 9; i >= 0; --i) {
        if(has[c[i]]) {
            c[i] = n + 1;
        } else {
            has[c[i]] = true;
        }
    }

    vector<ll> dp(n + 1, 0);
    vector<int> rec(n + 1, -1);
    for(int i = 1; i <= 9; ++i) {
        for(int j = 0; j + c[i] < n + 1; ++j) {
            if(dp[j + c[i]] <= dp[j] + 1) {
                dp[j + c[i]] = dp[j] + 1;
                rec[j + c[i]] = i;
            }
        }
    }

    int mxCnt = 0, mxIdx = 0, mxRec = -1;
    for(int i = 0; i < n + 1; ++i) {
        if(mxCnt < dp[i]) {
            mxCnt = dp[i];
            mxIdx = i;
            mxRec = rec[i];
        }
    }

    vector<int> res;

    for(int i = 0; i < n + 1; ++i) {
        if(dp[i] != mxCnt) continue;

        vector<int> tmp;
        int cur = i;
        while(rec[cur] != -1) {
            tmp.push_back(rec[cur]);
            cur -= c[rec[cur]];
        }
        sort(tmp.begin(), tmp.end());
        reverse(tmp.begin(), tmp.end());
        if(res.size() == 0 || res < tmp) res = tmp;
    }

    for(int v : res) cout << v;
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
