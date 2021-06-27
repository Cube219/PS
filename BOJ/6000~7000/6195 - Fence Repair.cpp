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

int n, d[20001];
priority_queue<ll, vector<ll>, greater<ll>> pq;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        pq.push(d[i]);
    }
    ll res = 0;
    while(pq.size() > 1) {
        ll p1 = pq.top();
        pq.pop();
        ll p2 = pq.top();
        pq.pop();
        res += p1 + p2;
        pq.push(p1 + p2);
    }
    cout << res;

    return 0;
}
