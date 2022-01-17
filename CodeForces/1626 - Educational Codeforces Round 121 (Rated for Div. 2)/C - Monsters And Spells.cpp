#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n;
    cin >> n;
    vector<int> k(n), h(n);
    for(auto& v : k) cin >> v;
    for(auto& v : h) cin >> v;

    ll res = 0;
    ll ed = k[n - 1];
    ll st = ed - h[n - 1];
    for(int i = n - 2; i >= 0; --i) {
        ll cur = k[i] - st;
        if(cur <= 0) {
            ll gap = ed - st;
            res += gap * (gap + 1) / 2;

            ed = k[i];
            st = ed - h[i];
            continue;
        }
        if(cur >= h[i]) continue;
        st = k[i] - h[i];
    }
    ll gap = ed - st;
    res += gap * (gap + 1) / 2;

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
