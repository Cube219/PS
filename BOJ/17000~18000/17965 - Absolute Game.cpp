#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9876543219999999;

int tNum;
ll n, a[1001], b[1001];

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
    for(int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    ll res = 0;
    sort(b, b + n);
    for(int i = 0; i < n; ++i) {
        int idx = lower_bound(b, b + n, a[i]) - b;

        ll gap = INF;
        if(idx < n) gap = b[idx] - a[i];
        if(idx > 0) {
            gap = min(gap, a[i] - b[idx - 1]);
        }
        res = max(res, gap);
    }
    cout << res;

    return 0;
}
