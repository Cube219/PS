#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, a[1000001];

int get(int idx)
{
    int res = 1;
    int l = idx - 1, r = idx + 1;
    while(l >= 0 && r < n) {
        if(a[l] != a[r]) break;
        res += 2;
        l--; r++;
        if(a[l] >= a[l + 1]) break;
    }

    return res;
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
        cin >> a[i];
    }
    int res = -1;
    for(int i = 1; i < n - 1; ++i) {
        if(a[i - 1] != a[i + 1]) continue;
        if(a[i] <= a[i - 1]) continue;
        res = max(res, get(i));
    }

    cout << res;

    return 0;
}
