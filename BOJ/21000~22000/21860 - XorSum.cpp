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
    vector<ll> d(n), d2;
    for(auto& v : d) {
        cin >> v;
    }

    sort(d.begin(), d.end());
    d2 = d;

    ll res = 0;
    for(int k = 30 - 1; k >= 0; --k) {
        ll cnt0 = 0, cnt1 = 0;
        int r0 = -1, r1 = -1, r2 = -1;
        ll k2 = (1LL << k);
        ll mask = (k2 << 1) - 1;
        int onest = n;
        for(int i = n - 1; i >= 0; --i) {
            ll r = d[i] & mask;
            if(d[i] & k2) onest = i;

            while(r0 < i && (d[r0 + 1] & mask) + r < k2) r0++;
            r1 = max(r1, r0);
            while(r1 < i && (d[r1 + 1] & mask) + r < k2 * 2) r1++;
            r2 = max(r2, r1);
            while(r2 < i && (d[r2 + 1] & mask) + r < k2 * 3) r2++;

            r0 = min(r0, i);
            r1 = min(r1, i);
            r2 = min(r2, i);

            cnt0 += r0 + 1;
            cnt1 += r1 - r0;
            cnt0 += r2 - r1;
            cnt1 += i - r2;
        }

        if(cnt1 & 1) res |= k2;

        if(k > 0) {
            d2.clear();
            int cur1 = 0, cur2 = onest;
            mask >>= 1;
            while(cur1 < onest || cur2 < n) {
                if(cur1 == onest) d2.push_back(d[cur2++]);
                else if(cur2 == n) d2.push_back(d[cur1++]);
                else if((d[cur1] & mask) < (d[cur2] & mask)) {
                    d2.push_back(d[cur1++]);
                } else {
                    d2.push_back(d[cur2++]);
                }
            }

            swap(d, d2);
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
