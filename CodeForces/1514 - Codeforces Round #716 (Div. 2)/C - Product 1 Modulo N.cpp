#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
bool has[100001];

int gcd(int a, int b)
{
    if(b == 0) return a;

    ll r = a % b;
    return gcd(b, r);
}


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    ll pd = 1;
    for(int i = 1; i < n; ++i) {
        if(gcd(n, i) == 1) {
            has[i] = true;
            pd *= (ll)i;
            pd %= n;
        }
    }
    if(pd % (ll)n != 1) {
        has[pd] = false;
    }
    int cnt = 0;
    for(int i = 1; i < n; ++i) {
        if(has[i] == true) cnt++;
    }
    cout << cnt << "\n";
    for(int i = 1; i < n; ++i) {
        if(has[i] == true) cout << i << " ";
    }

    return 0;
}
