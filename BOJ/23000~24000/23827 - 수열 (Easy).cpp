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

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    ll sum = 0, res = 0;
    for(int i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        res += (sum * a) % MOD;
        res %= MOD;
        sum = (sum + a) % MOD;
    }
    cout << res;

    return 0;
}
