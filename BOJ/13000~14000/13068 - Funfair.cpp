#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
double x;

struct Node
{
    int a, l, p;
};
Node d[101];
double dp[101][101];

double calc(double c, const Node& g)
{
    double dl = (double)g.l;
    double dp = (double)g.p;
    return c * (dp / 100.0 * dl / 100.0 - dl / 100.0 + 1.0) + (double)g.a * dp / 100.0;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> n >> k >> x;
        if(n == 0) break;

        for(int i = 0; i < n; ++i) {
            int a, l, p;
            cin >> a >> l >> p;
            d[i].a = a;
            d[i].l = l;
            d[i].p = p;
        }
        sort(d, d + n, [](const Node& l, const Node& r) {
            return l.a * l.p * (r.p * r.l - 100 * r.l) > r.a * r.p * (l.p * l.l - 100 * l.l);
        });

        dp[0][0] = x;
        dp[0][1] = calc(x, d[0]);

        for(int i = 1; i < n; ++i) {
            for(int j = 0; j <= k; ++j) {
                dp[i][j] = dp[i - 1][j];
            }
            for(int j = 1; j <= k; ++j) {
                if(dp[i - 1][j - 1] > 0.0) {
                    dp[i][j] = max(dp[i][j], calc(dp[i - 1][j - 1], d[i]));
                }
            }
        }
        cout << fixed << setprecision(2) << dp[n - 1][k] << "\n";
    }

    return 0;
}
