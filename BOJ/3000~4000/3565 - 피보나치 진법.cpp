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
    ll n;
    cin >> n;

    if(n == 0) {
        cout << "0\n";
        return;
    }

    vector<ll> f = { 1, 1 }, cnt = { 0, 1 }, cnt1 = { 0, 1 };
    ll sz = 2;
    while(cnt.back() < n) {
        ll nxt = f[sz - 2] + f[sz - 1];
        ll gap = f[sz - 1];

        f.push_back(nxt);
        cnt.push_back(cnt.back() + gap * sz);
        cnt1.push_back(cnt1.back() + cnt1[sz - 2] + gap);

        sz++;
    }

    ll res = 0;
    auto cal = [&](auto&& self, ll x, int idx) -> ll {
        if(x < 0 || idx < 0) return 0;
        if(f[idx] <= x) {
            return cnt1[idx - 1] + (x - f[idx] + 1) + self(self, x - f[idx], idx - 1);
        }
        return self(self, x, idx - 1);
    };
    res += cal(cal, f[sz - 1] - 1 + (n - cnt[sz - 2]) / (sz - 1), sz - 1);

    n -= cnt[sz - 2];
    ll lastV = f[sz - 1] + n / (sz - 1);
    n %= (sz - 1);

    for(int i = 0; i < n; ++i) {
        if(lastV >= f.back()) {
            res++;
            lastV -= f.back();
        }
        f.pop_back();
    }

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
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
