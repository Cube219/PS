#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 998244353;

struct Node
{
    int x;
    int y;
};

int n;
Node d[200001];
bool isact[200001];
ll dp[200001];
ll sum[200001];
int x[200001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y;
        x[i] = d[i].x;
        int c;
        cin >> c;
        if(c == 1) isact[i] = true;
    }

    for(int i = 0; i < n; ++i) {
        int idx = lower_bound(x, x + i + 1, d[i].y) - x;
        int curx = d[i].y;
        ll v = 0;
        v = d[i].x - curx;
        if(i > 0) v += sum[i - 1];
        if(idx > 0) v -= sum[idx - 1];
        v = (v + MOD) % MOD;

        dp[i] = v;
        sum[i] = dp[i];
        if(i > 0) sum[i] = (sum[i] + sum[i - 1]) % MOD;
    }

    int curx = 0;
    ll res = 0;
    for(int i = 0; i < n; ++i) {
        res = (res + d[i].x - curx) % MOD;
        curx = d[i].x;
        if(isact[i] == true) {
            res = (res + dp[i]) % MOD;
        }
    }
    res = (res + 1) % MOD;

    cout << res;

    return 0;
}
