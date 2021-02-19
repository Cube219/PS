#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, k;
int a[200005], d[200005];
int sum[200005], mn[200005];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int l = 1, r = n + 1;
    while(l + 1 < r) {
        int m = (l + r) / 2;

        for(int i = 0; i < n; ++i) {
            if(a[i] < m) d[i] = -1;
            else d[i] = 1;
        }

        sum[0] = d[0];
        mn[0] = min(0, sum[0]);
        for(int i = 1; i < n; ++i) {
            sum[i] = sum[i - 1] + d[i];
            mn[i] = min(mn[i - 1], sum[i]);
        }

        bool isPos = false;
        if(sum[k - 1] > 0) isPos = true;
        else {
            for(int i = k; i < n; ++i) {
                if(sum[i] - mn[i - k] > 0) {
                    isPos = true;
                    break;
                }
            }
        }

        if(isPos == true) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l;

    return 0;
}
