#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr ll MOD = 998244353;

int n;
ll d[200001];
ll res, curmin;
ll cnt;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    sort(d, d + n);
    res = (d[0] * d[0]) % MOD;
    curmin = d[0];
    for(int i = 1; i < n; ++i) {
        res = (res + d[i] * d[i]) % MOD;
        res = (res + d[i] * curmin) % MOD;
        curmin = (curmin * 2 + d[i]) % MOD;
    }

    cout << res;

    return 0;
}
