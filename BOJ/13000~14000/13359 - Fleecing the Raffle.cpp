#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

using ll = long long int;

ll n, p;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> p;
    ll x = n / (p - 1);
    
    double res = (double)p / (n + 1);
    for(int i = 2; i <= x; ++i) {
        res *= (double)(n - p + i);
        res /= (double)(n + i);
    }
    res *= (double)x;

    cout.precision(15);
    cout << res;

    return 0;
}
