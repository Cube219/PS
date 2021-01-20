#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
ll a[200001], diff[200001], diffabs[200001];

ll res, sum;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;
        sum = 0;

        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }

        for(int i = 1; i < n; i++) {
            diff[i] = a[i] - a[i - 1];
            diffabs[i] = abs(diff[i]);
            sum += diffabs[i];
        }

        res = diffabs[1];
        for(int i = 1; i < n - 1; i++) {
            if(diff[i] >= 0 && diff[i + 1] >= 0) continue;
            if(diff[i] <= 0 && diff[i + 1] <= 0) continue;

            ll tmp = min(diffabs[i], diffabs[i+1]);
            if(res < tmp * 2) res = tmp * 2;
        }
        if(res < diffabs[n - 1]) {
            res = diffabs[n - 1];
        }

        cout << sum - res << "\n";
    }

    return 0;
}
