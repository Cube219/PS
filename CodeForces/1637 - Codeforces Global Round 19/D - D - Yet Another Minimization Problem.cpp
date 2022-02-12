#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    struct Node
    {
        ll a, b;
    };
    int n;
    cin >> n;
    vector<Node> d(n);
    for(auto& v : d) {
        cin >> v.a;
    }
    for(auto& v : d) {
        cin >> v.b;
    }

    map<pair<ll, ll>, ll> mp;
    mp.insert({ {0, 0}, 0 });
    for(auto& v : d) {
        map<pair<ll, ll>, ll> mp2;
        for(auto [vp, val] : mp) {
            auto tmp = vp;
            tmp.first += v.a;
            tmp.second += v.b;

            auto it = mp2.find(tmp);
            if(it == mp2.end()) {
                it = mp2.insert({ tmp, LNF }).first;
            }
            ll vv = val + vp.first * v.a + vp.second * v.b;
            if(vv < it->second) it->second = vv;

            tmp = vp;
            tmp.first += v.b;
            tmp.second += v.a;

            it = mp2.find(tmp);
            if(it == mp2.end()) {
                it = mp2.insert({ tmp, LNF }).first;
            }
            vv = val + vp.first * v.b + vp.second * v.a;
            if(vv < it->second) it->second = vv;
        }
        mp = std::move(mp2);
    }

    ll res = LNF;
    for(auto [vp, val] : mp) {
        res = min(res, val);
    }
    res *= 2;
    for(auto& v : d) {
        res += v.a * v.a * (n - 1);
        res += v.b * v.b * (n - 1);
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
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
