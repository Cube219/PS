#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iomanip>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    string str;
    cin >> str;
    int n = str.size();
    vector<int> d(n);
    int dv = 0;
    for(int i = 0; i < n; ++i) {
        d[i] = str[i] - '0';
        dv *= 10;
        dv += d[i];
    }
    int a, b;
    cin >> a >> b;

    struct Node
    {
        double mn, mx;
    };
    vector<Node> dp(1 << n, { -1, -1 });

    auto bt = [&](auto&& self, int cur) -> Node {
        if(dp[cur].mn >= 0) return dp[cur];

        dp[cur] = {0, 0};

        for(int i = 1; i <= 6; ++i) {
            for(int j = 1; j <= 6; ++j) {
                double mn = INF, mx = -1;
                for(int rm = cur; rm > 0; rm = (rm - 1) & cur) {
                    int sum = 0;
                    for(int k = 0; k < n; ++k) {
                        if(rm & (1 << k)) sum += d[k];
                    }
                    if(sum != i + j) continue;

                    auto res = self(self, cur ^ rm);
                    mn = min(mn, res.mn);
                    mx = max(mx, res.mx);
                }
                if(mn == INF) {
                    mn = 0;
                    for(int k = 0; k < n; ++k) {
                        if(cur & (1 << k)) {
                            mn *= 10;
                            mn += d[k];
                        }
                    }
                    mx = mn;
                }
                dp[cur].mn += mn;
                dp[cur].mx += mx;
            }
        }

        dp[cur].mn /= 36;
        dp[cur].mx /= 36;

        return dp[cur];
    };
    int all = (1 << n) - 1;
    bt(bt, all);

    int mnRemove = -1, mxRemove = -1;
    double mnRes = INF, mxRes = -1;
    for(int rm = all; rm > 0; rm = (rm - 1) & all) {
        int sum = 0, list = 0;
        for(int k = 0; k < n; ++k) {
            if(rm & (1 << k)) {
                sum += d[k];
                list = list * 10 + d[k];
            }
        }
        if(sum != a + b) continue;

        int cur = all ^ rm;
        if(mnRes > dp[cur].mn) {
            mnRes = dp[cur].mn;
            mnRemove = list;
        }
        if(mxRes < dp[cur].mx) {
            mxRes = dp[cur].mx;
            mxRemove = list;
        }
    }

    if(mnRemove == -1) mnRes = dv;
    if(mxRemove == -1) mxRes = dv;

    cout << fixed << setprecision(5);
    cout << mnRemove << " " << mnRes << "\n";
    cout << mxRemove << " " << mxRes << "\n";
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
