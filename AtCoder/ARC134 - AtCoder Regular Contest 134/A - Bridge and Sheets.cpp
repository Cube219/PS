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
    ll n, l, w;
    cin >> n >> l >> w;
    struct Node
    {
        ll l, r;
    };
    vector<Node> remain;
    ll cur = -1;
    for(int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        if(cur < x) {
            remain.push_back({ cur, x - 1 });
        }
        cur = x + w;
    }
    if(cur < l) remain.push_back({ cur, l - 1 });

    ll res = 0;
    cur = -1;
    for(auto& v : remain) {
        if(cur <= v.r) {
            ll cnt = (v.r - max(v.l - 1, cur)) / w;
            if((v.r - max(v.l - 1, cur)) % w != 0) {
                cnt++;
            } else {
                cnt = cnt;
            }
            res += cnt;
            cur = max(v.l - 1, cur) + w * cnt;
        }
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
