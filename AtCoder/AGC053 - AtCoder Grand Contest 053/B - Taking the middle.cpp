#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

using ll = long long int;

int n;
ll a[400002];
ll sum, res;

priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n * 2; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    int l = n;
    int r = n + 1;
    pq.push({ a[l], l });
    pq.push({ a[r], r });

    for(int cnt = 0; cnt < n; ++cnt) {
        res += pq.top().first;
        pq.pop();
        l--;
        r++;
        pq.push({ a[l], l });
        pq.push({ a[r], r });
    }

    cout << sum - res;

    return 0;
}
