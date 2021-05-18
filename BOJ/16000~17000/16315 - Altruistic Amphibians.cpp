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
    int l, w, h;
};

int n, l;
Node d[100001];
int dp[100000002];
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> l;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].l >> d[i].w >> d[i].h;
    }
    sort(d, d + n, [](const Node& l, const Node& r) {
        if(l.w == r.w) return l.h > r.h;
        return l.w > r.w;
    });

    if(d[0].l > l) res++;
    for(int i = 0; i < d[0].w; ++i) {
        dp[i] = d[0].h;
    }
    for(int i = 1; i < n; ++i) {
        if(dp[d[i].w] + d[i].l > l) res++;

        for(int j = 0; j < d[i].w; ++j) {
            dp[j] = max(dp[j], dp[j + d[i].w] + d[i].h);
            if(dp[j] > l) dp[j] = l + 1;
        }
    }

    cout << res;

    return 0;
}
