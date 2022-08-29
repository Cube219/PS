#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

void solve()
{
    int n; ll t;
    cin >> n >> t;
    string str;
    cin >> str;

    vector<int> d(n);
    for(int i = 0; i < n; ++i) d[i] = str[i] - '0';

    vector<int> nxt(n);
    for(int i = 50 - 1; i >= 0; --i) {
        if(t & (1ll << i)) {
            fill(nxt.begin(), nxt.end(), 0);
            ll dj = 1ll << i;
            for(ll j = 0; j < n; ++j) {
                ll l = (j - dj) % n; l = (l + n) % n;
                ll r = (j + dj) % n;
                nxt[l] ^= d[j];
                nxt[r] ^= d[j];
            }
            swap(d, nxt);
        }
    }

    for(int v : d) cout << v;
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
