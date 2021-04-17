#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MOD = 1000000007;

struct Node
{
    int l, r;
};

int n;
Node d[100001];
int num[200001];
ll p2[100001];
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        d[i] = { a, b };
    }

    p2[0] = 1;
    for(int i = 1; i <= n; ++i) {
        p2[i] = (p2[i - 1] * 2) % MOD;
    }

    for(int i = 0; i < n; ++i) {
        num[d[i].l]++;
        num[d[i].r]--;
    }
    for(int i = 1; i <= n * 2; ++i) {
        num[i] += num[i - 1];
    }

    for(int i = 0; i < n; ++i) {
        res += p2[n - 1 - num[d[i].l - 1]];
        res %= MOD;
    }

    cout << res;

    return 0;
}
