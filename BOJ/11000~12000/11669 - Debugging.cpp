#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999999;

int n, run, ins;
ll dp[1000001];

ll p(int num)
{
    if(dp[num] != 0) return dp[num];
    if(num <= 1) return 0;

    dp[num] = INF;
    for(int i = 2; i <= num; ++i) {
        int nxt = num / i;
        if(num % i != 0) nxt++;
        dp[num] = min(dp[num], (ll)run + (ll)ins * (i - 1) + p(nxt));
    }
    return dp[num];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> run >> ins;

    cout << p(n);

    return 0;
}
