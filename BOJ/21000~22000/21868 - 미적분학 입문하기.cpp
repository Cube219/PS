#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll eu, ed;
ll a, b;
ll x0;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> eu >> ed;
    cin >> a >> b;
    cin >> x0;
    ll l = a * x0 + b;

    ed *= abs(a);
    if(ed == 0) eu = 0;
    if(ed == 0) eu = 0;
    cout << l << "\n";
    cout << eu << " " << ed;

    return 0;
}
