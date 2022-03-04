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

constexpr ll MX = 1'00000'00000'00;
vector<ll> fac;

void solve()
{
    ll n;
    cin >> n;

    auto getBit = [](ll x) {
        int res = 0;
        for(int i = 0; i < 41; ++i) {
            bool has = (x & (1LL << i)) ? true : false;
            if(has) res++;
        }
        return res;
    };

    int res = INF;

    auto bt = [&](auto&& self, int idx, ll cur, int cnt) {
        if(cur > n) return;
        if(idx == fac.size()) {
            res = min(res, getBit(n - cur) + cnt);
            return;
        }

        self(self, idx + 1, cur, cnt);
        self(self, idx + 1, cur + fac[idx], cnt + 1);
    };
    bt(bt, 0, 0, 0);

    cout << res << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ll cur = 1 * 2;
    for(int i = 3; i <= 100000; ++i) {
        cur *= i;
        if(cur > MX) break;
        fac.push_back(cur);
    }

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
