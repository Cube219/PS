#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll n, m, a;
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> a;
    res = 3;
    if(a % m == 0 || a % n == 0) res = 1;
    else {
        for(int i = 1; i < n; ++i) {
            ll remain = a - i * m;
            if(remain > 0) {
                if(remain % (n - i) == 0) {
                    res = 2;
                    break;
                }
            } else {
                if(a % i == 0) {
                    res = 2;
                    break;
                }
            }
        }
        for(int i = 1; i < m; ++i) {
            ll remain = a - i * n;
            if(remain > 0) {
                if(remain % (m - i) == 0) {
                    res = 2;
                    break;
                }
            } else {
                if(a % i == 0) {
                    res = 2;
                    break;
                }
            }
        }
    }

    cout << res;

    return 0;
}
