#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    ll a, x;
};

int n, q;
Node d[200005];
ll lsum1[200005], rsum1[200005], lsum2[200005], rsum2[200005];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i].a >> d[i].x;
    }
    sort(d + 1, d + n + 1, [](const Node& l, const Node& r) {
        return l.x < r.x;
    });

    for(int i = 1; i <= n; ++i) {
        lsum1[i] = lsum1[i - 1] + d[i].a;
        lsum2[i] = lsum2[i - 1] + d[i].a * d[i].x;
    }
    for(int i = n; i >= 1; --i) {
        rsum1[i] = rsum1[i + 1] + d[i].a;
        rsum2[i] = rsum2[i + 1] + d[i].a * d[i].x;
    }

    for(int i = 0; i < q; ++i) {
        ll p;
        cin >> p;
        int idx = lower_bound(d + 1, d + 1 + n, p, [](const Node& l, ll v) { return l.x < v; }) - d;

        ll res = 0;
        res += p * lsum1[idx - 1];
        res -= lsum2[idx - 1];
        res += rsum2[idx];
        res -= p * rsum1[idx];

        cout << res << "\n";
    }

    return 0;
}
