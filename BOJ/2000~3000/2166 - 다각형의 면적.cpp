#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

struct Dot
{
    ll x;
    ll y;
};
int n;
Dot d[10001];

ll ccw(ll x1, ll y1, ll x2, ll y2)
{
    return x1 * y2 - x2 * y1;
}

ll res;


int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d[i].x >> d[i].y;
    }

    for(int i = 1; i < n - 1; i++) {
        res += ccw(d[i].x - d[0].x, d[i].y - d[0].y, d[i + 1].x - d[0].x, d[i + 1].y - d[0].y);
    }

    printf("%.1f", (double)llabs(res) / 2.0);

    return 0;
}
