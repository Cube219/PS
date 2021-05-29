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
int d, s;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> d >> s;
    ll a = n * d - s * k;
    double b = (double)a / (n - k);
    if(b > 100.0 || b < 0.0) cout << "impossible";
    else cout <<fixed <<setprecision(10) << b;

    return 0;
}
