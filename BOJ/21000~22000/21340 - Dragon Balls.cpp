#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <cmath>
#include <limits.h>
using namespace std;

using ll = long long int;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution(0, INT_MAX);

int n;


int main(void)
{
#ifdef CUBE_PS
    // freopen("input.txt", "r", stdin);
#endif

    cin >> n;

    for(int i = 0; i < n; ++i) {
        ll x = distribution(rng) % 1000000;
        ll y = 0;
        cout << x << " " << y << endl;
        ll t1, t2;
        cin >> t1;
        if(t1 == 0) continue;
        cout << x + 1 << " " << y << endl;
        cin >> t2;
        if(t2 == 0) continue;
        if(t1 == t2) {
            i--; continue;
        }

        ll a = (2 * x + 1) - t2 + t1;
        a /= 2;
        ll b = t1 - (x - a) * (x - a);
        b = (ll)sqrt(b);
        cout << a << " " << b << endl;
        cin >> t1;
        if(t1 != 0) {
            i--; continue;
        }
    }


    return 0;
}
