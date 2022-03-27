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
    int n, q;
    cin >> n >> q;

    ll myCnt = 0, otherCnt = 0, mx = 0;
    vector<ll> cnt(n, 0);
    for(int i = 0; i < q; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int x, p;
            cin >> x >> p;
            p--;
            if(p == n) myCnt += x;
            else {
                otherCnt += x;
                cnt[p] += x;
                mx = max(mx, cnt[p]);
            }
        } else {
            int x, y;
            cin >> x >> y;

            ll otherMx = (myCnt + x - 1) * n;
            if(myCnt + x > mx && otherMx >= otherCnt + y) cout << "YES\n";
            else cout << "NO\n";
        }
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
