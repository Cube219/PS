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
    int n;
    cin >> n;
    vector<int> d(n);
    vector<int> cnt(30, 0);
    ll res = 0;
    for(auto& v : d) {
        cin >> v;
        res += v;
        int tmp = v;
        for(int i = 0; i < 30; ++i) {
            if(tmp & (1 << i)) cnt[i]++;
        }
    }

    for(int v : d) {
        ll cur = 0;
        for(int i = 0; i < 30; ++i) {
            if(v & (1 << i)) {
                cur += (1LL << i) * (n - cnt[i]);
            } else {
                cur += (1LL << i) * cnt[i];
            }
        }
        res = max(res, cur);
    }

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
