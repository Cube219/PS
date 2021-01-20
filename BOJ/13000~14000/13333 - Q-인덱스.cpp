#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int n, d[1001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }

    sort(d, d + n);

    int res = -1;

    for(int i = 0; i <= n; i++) {
        auto it = lower_bound(d, d + n, i);

        int down = it - d;
        int up = n - down;

        if(up >= i && down <= i) res = i;
    }

    cout << res;

    return 0;
}
