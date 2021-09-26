#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

using ll = long long int;

int n, k;
ll t[100001];
priority_queue<ll, vector<ll>, greater<ll>> pq;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> t[i];
        if(i > 0) {
            pq.push(t[i] - t[i - 1] - 1);
        }
    }

    ll res = 0;
    for(int i = 0; i < n - k; ++i) {
        res += pq.top();
        pq.pop();
    }

    cout << res + n;

    return 0;
}
