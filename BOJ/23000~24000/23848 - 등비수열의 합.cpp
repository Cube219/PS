#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    ll n;
    cin >> n;

    for(ll r = 2; r <= 1000000; ++r) {
        ll cur = r * r + r + 1;
        ll curr = r * r;
        for(int i = 3; i <= 50; ++i) {
            if(n % cur == 0) {
                cout << i << "\n";
                ll a = n / cur;
                for(int j = 0; j < i; ++j) {
                    cout << a << " ";
                    a *= r;
                }
                return;
            }
            if(n < cur) break;
            curr *= r;
            cur += curr;
        }
    }

    cout << "-1";
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        // cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}
