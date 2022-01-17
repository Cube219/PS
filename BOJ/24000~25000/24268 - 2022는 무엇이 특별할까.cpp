#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, d;
    cin >> n >> d;

    vector<int> p(d);
    iota(p.begin(), p.end(), 0);

    ll res = LNF;
    int rng = 1;
    for(int i = 1; i <= d; ++i) {
        rng *= i;
    }
    for(int i = 0; i < rng; ++i) {
        if(p[0] != 0) {
            ll v = 0;
            for(int j = 0; j < d; ++j) {
                v *= d;
                v += p[j];
            }
            if(v > n) res = min(res, v);
        }
        next_permutation(p.begin(), p.end());
    }

    if(res == LNF) res = -1;
    cout << res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
