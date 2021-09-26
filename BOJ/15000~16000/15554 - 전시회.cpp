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
    ll sz, v;
};

int n;
Node d[500001];
ll sum[500001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].sz >> d[i].v;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.sz < r.sz;
    });
    sum[0] = d[0].v;
    for(int i = 1; i < n; ++i) {
        sum[i] = sum[i - 1] + d[i].v;
    }

    ll res = d[0].v;
    ll mxv = d[0].sz;
    for(int i = 1; i < n; ++i) {
        res = max(res, d[i].v);
        res = max(res, sum[i] - d[i].sz + mxv);
        mxv = max(mxv, d[i].sz - sum[i - 1]);
    }

    cout << res;

    return 0;
}
