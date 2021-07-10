#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000000 + 7;

int n, c[200001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    sort(c, c + n);
    ll res = 1;
    for(int i = 0; i < n; ++i) {
        ll num = c[i] - i;
        res *= num;
        res %= MOD;
    }
    cout << res;

    return 0;
}
