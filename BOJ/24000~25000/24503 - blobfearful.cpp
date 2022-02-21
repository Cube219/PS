#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

vector<pair<ll, int>> largePrimeFac(ll v)
{
    vector<pair<ll, int>> res;
    ll sqv = sqrtl(v);

    for(ll f = 2; f <= sqv && v > 1; ++f) {
        if(v % f != 0) continue;
        res.emplace_back(f, 0);
        while(v % f == 0) {
            res.back().second++;
            v /= f;
        }
    }
    if(v > 1) res.emplace_back(v, 1);

    return res;
}

void solve()
{
    ll k;
    cin >> k;

    auto pf = largePrimeFac(k);
    vector<vector<ll>> lim(pf.size());
    for(int i = 0; i < pf.size(); ++i) {
        lim[i].resize(pf[i].second + 1);

        ll cur = 0, cur2 = -1;
        ll factor = pf[i].first;
        lim[i][0] = 1;
        for(int j = 1; j <= pf[i].second; ++j) {
            if(cur2 % factor != 0) {
                cur += factor;
                cur2 = cur;
            }
            lim[i][j] = cur;
            cur2 /= factor;
        }
    }

    int q;
    cin >> q;
    for(int qq = 0; qq < q; ++qq) {
        ll a;
        cin >> a;
        ll res = 0;
        for(int i = 0; i < pf.size(); ++i) {
            ll factor = pf[i].first;
            int idx = lim[i].size() - 1;
            while(a % factor == 0 && idx > 0) {
                idx--;
                a /= factor;
            }
            res = max(res, lim[i][idx]);
        }

        cout << res << " ";
    }
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
