#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <math.h>
using namespace std;

using ll = long long int;

int tNum;
ll n, x;
ll a;
ll sum1, sum2;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        sum1 = 0;
        sum2 = 0;
        cin >> n >> x;
        for(int i = 0; i < n; i++) {
            cin >> a;
            sum1 += ceil((double)a / x);
            sum2 += a;
        }
        sum2 = ceil((double)sum2 / x);
        cout << sum2 << " " << sum1 << "\n";
    }

    return 0;
}
