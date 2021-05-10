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
    int a, c;
};

int n;
Node d[100001];
ll dp[100001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a, c;
        cin >> a >> c;
        d[i] = { a, c };
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        return l.a < r.a;
    });

    ll maxv = d[0].a + d[0].c;
    ll maxidx = 0;
    for(int i = 1; i < n; ++i) {
        dp[i] = dp[i - 1] + max(d[i].a - d[maxidx].a - d[maxidx].c, 0);
        if(maxv < d[i].a + d[i].c) {
            maxv = d[i].a + d[i].c;
            maxidx = i;
        }
    }
    ll res = 0;
    for(int i = 0; i < n; ++i) {
        res += d[i].c;
    }
    cout << res + dp[n - 1];

    return 0;
}
