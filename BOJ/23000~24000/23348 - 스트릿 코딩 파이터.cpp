#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c, n;
    cin >> a >> b >> c >> n;
    ll res = 0;
    for(int i = 0; i < n; ++i) {
        ll cur = 0;
        for(int j = 0; j < 3; ++j) {
            ll v1, v2, v3;
            cin >> v1 >> v2 >> v3;
            cur += v1 * a + v2 * b + v3 * c;
        }
        res = max(res, cur);
    }
    cout << res;

    return 0;
}
