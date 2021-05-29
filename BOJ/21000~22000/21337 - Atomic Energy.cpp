#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

int n, q;
ll dp[10005];
ll a[101];

struct Node
{
    int idx;
    double dv;
};
Node d[101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        dp[i] = a[i];
        d[i - 1] = { (int)i, (double)a[i] / i };
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.dv < r.dv;
    });

    int range = 10000;
    for(int i = n + 1; i <= range; ++i) {
        dp[i] = INF;
        for(int j = 1; j <= i && j <= n; ++j) {
            ll v = dp[i - j];
            if(i - j <= n) v = a[i - j];
            if(dp[i] > v + a[j]) {
                dp[i] = v + a[j];
            }
        }
    }

    for(int i = 0; i < q; ++i) {
        ll k;
        cin >> k;
        if(k <= range) {
            cout << dp[k] << "\n";
        } else {
            ll num = (k - range) / d[0].idx;
            k = k - num * d[0].idx;
            while(k > 10000) {
                k -= d[0].idx;
                num++;
            }
            ll res = a[d[0].idx] * num + dp[k];
            cout << res;
            cout << "\n";
        }
    }

    return 0;
}
