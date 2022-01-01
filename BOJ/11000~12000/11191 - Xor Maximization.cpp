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
    vector<ll> d(n);
    for(auto& v : d) cin >> v;

    // max 60 bits
    vector<ll> basis(60, 0);

    for(ll mask : d) {
        while(mask > 0) {
            int msb = 0;
            ll tmp = mask;
            for(int i = 0; i < 60; ++i) {
                if(tmp & 1) msb = i;
                tmp >>= 1;
                if(tmp == 0) break;
            }

            if(basis[msb] == 0) {
                basis[msb] = mask;
                break;
            }
            mask ^= basis[msb];
        }
    }

    ll res = 0;
    for(int i = 60 - 1; i >= 0; --i) {
        if((res & (1LL << i)) > 0) continue;
        res ^= basis[i];
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
