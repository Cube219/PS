#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
ll c;
ll d[250001];
ll l[250001];
ll r[250001];
ll res = 999999999999999999;
int rIdx;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> c;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
    }
    for(int i = 1; i < n; i++) {
        ll v;
        if(d[i - 1] >= d[i]) v = d[i - 1] - d[i];
        else v = c - (d[i] - d[i - 1]);
        l[i] = l[i - 1] + v;
    }
    for(int i = n - 2; i >= 0; i--) {
        ll v;
        if(d[i] <= d[i + 1]) v = d[i + 1] - d[i];
        else v = c - (d[i] - d[i + 1]);
        r[i] = r[i + 1] + v;
    }

    for(int i = 0; i < n; i++) {
        ll t = max(l[i], r[i]);
        if(t < res) {
            res = t;
            rIdx = i;
        }
    }
    cout << rIdx + 1 << "\n";
    cout << res;

    return 0;
}
