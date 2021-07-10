#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, x, a[101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> x;
    ll sum = 0;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
        if(i % 2 == 1) a[i]--;
        sum += a[i];
    }
    if(sum <= x) cout << "Yes";
    else cout << "No";

    return 0;
}
