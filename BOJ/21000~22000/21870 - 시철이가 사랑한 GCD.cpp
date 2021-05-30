#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int gcd(int a, int b)
{
    if(a < b) swap(a, b);
    if(b == 0) return a;
    return gcd(b, a % b);
}

int n;
int d[200001];

ll getgcd(int l, int r)
{
    int res = d[l];
    for(int i = l + 1; i <= r; ++i) {
        res = gcd(res, d[i]);
    }
    return res;
}

ll p(int l, int r)
{
    if(l == r) return d[l];

    int num = (r - l + 1);
    int m = l + (num / 2) - 1;

    ll lres = getgcd(l, m) + p(m + 1, r);
    ll rres = getgcd(m + 1, r) + p(l, m);
    return max(lres, rres);
}

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

    cout << p(0, n - 1);

    return 0;
}
