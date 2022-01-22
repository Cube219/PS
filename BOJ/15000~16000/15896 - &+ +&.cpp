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
    vector<int> a(n), b(n), cnta(30, 0), cntb(30, 0);
    for(auto& v : a) {
        cin >> v;
        int tmp = v;
        for(int i = 0; i < 30 && tmp > 0; ++i, tmp >>= 1) {
            if(tmp & 1) cnta[i]++;
        }
    }
    for(auto& v : b) {
        cin >> v;
        int tmp = v;
        for(int i = 0; i < 30 && tmp > 0; ++i, tmp >>= 1) {
            if(tmp & 1) cntb[i]++;
        }
    }

    ll res1 = 0;
    for(int i = 0; i < 30; ++i) {
        ll v = (1LL << i) * cnta[i] % 1999;
        v = v * cntb[i] % 1999;
        res1 = (res1 + v) % 1999;
    }

    ll res2 = 0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> a2 = a;
    vector<int> b2 = b;
    for(int k = 30 - 1; k >= 0; --k) {
        int mask = (1 << (k + 1)) - 1;
        int k2 = (1 << k);

        int r1 = -1, r2 = -1, r3 = -1;
        int cnt0 = 0;
        for(int i = n - 1; i >= 0; --i) {
            int cur = b[i] & mask;
            while(r1 < n - 1 && (a[r1 + 1] & mask) + cur < k2) r1++;
            r2 = max(r2, r1);
            while(r2 < n - 1 && (a[r2 + 1] & mask) + cur < k2 * 2) r2++;
            r3 = max(r3, r2);
            while(r3 < n - 1 && (a[r3 + 1] & mask) + cur < k2 * 3) r3++;

            cnt0 += r1 + 1;
            cnt0 += r3 - r2;
        }

        if(cnt0 == 0) res2 |= k2;

        if(k > 0) {
            mask >>= 1;
            auto mv = [n, k2, mask](vector<int>& d, vector<int>& d2) {
                int onest = n;
                for(int i = 0; i < n; ++i) {
                    if(d[i] & k2) {
                        onest = i;
                        break;
                    }
                }
                d2.clear();
                int cur1 = 0, cur2 = onest;
                while(cur1 < onest || cur2 < n) {
                    if(cur1 == onest) d2.push_back(d[cur2++]);
                    else if(cur2 == n) d2.push_back(d[cur1++]);
                    else if((d[cur1] & mask) < (d[cur2] & mask)) d2.push_back(d[cur1++]);
                    else d2.push_back(d[cur2++]);
                }
                swap(d, d2);
            };
            mv(a, a2);
            mv(b, b2);
        }
    }

    cout << res1 << " " << res2;
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
