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
    int t, k;
    cin >> t >> k;

    vector<ll> num, sum;
    int cursz = 1;
    num.push_back(1);
    sum.push_back(1);
    ll nxtk = k;
    for(int i = 2; sum.back() < 2000000000; ++i) {
        ll v = num.back();
        if(i == nxtk) {
            cursz++;
            nxtk *= k;
        }
        v += cursz;
        num.push_back(v);

        sum.push_back(sum.back() + num.back());
    }

    for(int tt = 0; tt < t; ++tt) {
        int n;
        cin >> n;

        int i;
        for(i = 0; n - sum[i] > 0; ++i) {}
        if(i > 0) n -= sum[i - 1];

        cursz = 1;
        nxtk = k;
        int j;
        for(j = 1; ; ++j) {
            if(j == nxtk) {
                cursz++;
                nxtk *= k;
            }
            if(n - cursz <= 0) break;
            n -= cursz;
        }
        vector<int> res;
        for(; j > 0; j /= k) res.push_back(j % k);
        reverse(res.begin(), res.end());
        cout << res[n - 1] << "\n";
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
