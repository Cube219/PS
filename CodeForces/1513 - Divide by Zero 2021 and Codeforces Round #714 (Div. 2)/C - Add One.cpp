#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

int tNum;
int n, m;
ll dNum[11];
ll d[11], dp[200001][11];

void init()
{
    for(int st = 0; st < 10; ++st) {
        for(int i = 0; i < 10; ++i) {
            d[i] = 0;
        }
        d[st] = 1;
        dp[0][st] = 1;
        for(int i = 1; i <= 200000; ++i) {
            ll g = d[9];
            for(int j = 9; j >= 1; --j) {
                d[j] = d[j - 1];
            }
            d[0] = g;
            d[1] += g;
            d[1] = d[1] % MOD;

            for(int j = 0; j < 10; ++j) {
                dp[i][st] += d[j];
                dp[i][st] = dp[i][st] % MOD;
            }
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < 10; ++i) {
            dNum[i] = 0;
        }

        while(n > 0) {
            dNum[n % 10]++;
            n /= 10;
        }

        ll rr = 0;
        for(int i = 0; i < 10; ++i) {
            rr += dNum[i] * dp[m][i];
            rr = rr % MOD;
        }

        cout << rr << "\n";
    }

    return 0;
}
