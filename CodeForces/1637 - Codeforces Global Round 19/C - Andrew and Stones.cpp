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
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    vector<char> isOdd(n, false);
    vector<ll> cnt(n, 0);
    ll res = 0;
    for(int i = 1; i < n - 1; ++i) {
        if(d[i] & 1) isOdd[i] = true;
        res += d[i] / 2;
        cnt[i] = d[i] / 2;
    }

    auto process = [&]() {
        ll res2 = 0;
        ll lcnt = 0, rcnt = 0, usedRcnt = 0;
        for(int i = 1; i < n - 1; ++i) {
            rcnt += cnt[i];
        }
        for(int i = 1; i < n - 1; ++i) {
            ll myCnt = d[i] / 2;
            if(myCnt <= usedRcnt) {
                usedRcnt -= myCnt;
            } else {
                myCnt -= usedRcnt;
                usedRcnt = 0;
                rcnt -= myCnt;
            }

            if(isOdd[i] == true) {
                if(lcnt > 0) {
                    lcnt--;
                    res2++;
                } else if(rcnt > 0) {
                    rcnt--;
                    usedRcnt++;
                    res2++;
                } else {
                    res2 = INF;
                    break;
                }
            }

            lcnt += (d[i] + 1) / 2;
        }
        return res2;
    };

    ll v = process();
    reverse(d.begin(), d.end());
    reverse(isOdd.begin(), isOdd.end());
    reverse(cnt.begin(), cnt.end());
    ll v2 = process();

    v = min(v, v2);
    if(v >= INF) res = -1;
    else res += v;

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
