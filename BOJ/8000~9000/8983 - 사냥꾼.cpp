#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string.h>
using namespace std;

using lli = long long int;

int m, n, l;
int mx[100001];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n >> l;
    for(int i = 0; i < m; i++) {
        cin >> mx[i];
    }
    
    sort(mx, mx + m);

    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if(y > l) continue;

        int left = x - (l - y);
        int right = x + (l - y);

        auto leftIter = lower_bound(mx, mx + m, left);
        auto rightIter = upper_bound(mx, mx + m, right);

        int leftIdx = leftIter - mx;
        int rightIdx = rightIter - mx;

        if(leftIdx <= rightIdx - 1) res++;
    }

    cout << res;

    return 0;
}
