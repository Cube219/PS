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
    ll x, d;
    cin >> x >> d;

    int num = 0;
    while(x % d == 0) {
        num++;
        x /= d;
    }

    if(num <= 1) {
        cout << "NO\n";
        return;
    }

    auto pf = largePrimeFac(x);
    int cnt = 0;
    for(auto [p, pn] : pf) {
        cnt += pn;
    }
    if(cnt >= 2) {
        cout << "YES\n";
        return;
    }

    // 남은 소수 0~1개
    auto pf2 = largePrimeFac(d);

    cnt = 0;
    for(auto [p, pn] : pf2) {
        cnt += pn;
    }
    if(num > 3 && cnt >= 2) {
        cout << "YES\n";
        return;
    }

    if(num < 3) {
        cout << "NO\n";
        return;
    }
    // 남은 소수 0~1개, 나눠진 수 3개
    // 남은 소수와 곱해서 d의 배수가 아닌 것을 구함
    for(auto [p, pn] : pf2) {
        if((x * p) % d != 0) {
            cout << "YES\n";
            return;
        }
    }

    cout << "NO\n";
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
