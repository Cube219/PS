#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
int dp[200001];
int maxL;
struct Food
{
    int p;
    int s;
};
Food d[1001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        maxL = 0;

        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> d[i].p >> d[i].s;
            if(maxL < d[i].p + d[i].s) maxL = d[i].p + d[i].s;
        }
        sort(d, d + n, [](const Food& l, const Food& r) {
            return l.p + l.s > r.p + r.s;
        });

        for(int i = 0; i <= maxL; i++) {
            dp[i] = 0;
        }

        for(int i = 0; i < n; i++) {
            int p = d[i].p;
            int s = d[i].s;
            for(int j = 0; j <= p; j++) {
                if(dp[j] < j + s) dp[j] = j + s;
                if(dp[j] < dp[j + s]) {
                    dp[j] = dp[j + s];
                }
            }
        }

        cout << "Case #" << tt << ": " << dp[0] << "\n";
    }

    return 0;
}
