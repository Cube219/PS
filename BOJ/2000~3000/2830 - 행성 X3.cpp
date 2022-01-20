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
    vector<int> bits(20, 0);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        for(int j = 0; j < 20; ++j) {
            if(a == 0) break;
            if(a & 1) bits[j]++;
            a >>= 1;
        }
    }

    ll res = 0;
    for(int i = 0; i < 20; ++i) {
        ll num = (ll)bits[i] * (n - bits[i]);
        res += (1LL << i) * num;
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
