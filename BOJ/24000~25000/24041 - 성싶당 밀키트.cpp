#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n, g, k;
    cin >> n >> g >> k;
    vector<ll> s(n), l(n), o(n);
    for(int i = 0; i < n; ++i) {
        cin >> s[i] >> l[i] >> o[i];
    }

    auto ck = [&](ll x) -> bool {
        if(x == 14) {
            x = 14;
        }
        priority_queue<ll> pq;
        ll cur = 0;
        for(int i = 0; i < n; ++i) {
            ll v = s[i] * max(1ll, x - l[i]);
            cur += v;
            if(o[i] == 1) {
                pq.push(v);
            }
        }

        int remain = k;
        while(cur > g && pq.empty() == false && remain > 0) {
            cur -= pq.top();
            pq.pop();
            remain--;
        }

        if(cur <= g) return true;
        else return false;
    };

    ll lo = 0, hi = 3'000'000'001;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(ck(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    cout << lo;
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
