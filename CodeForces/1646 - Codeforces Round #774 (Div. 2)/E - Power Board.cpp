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

    ll n, m;
    cin >> n >> m;

    vector<ll> num(21, 0);
    vector<char> has(20 * m + 1, false);
    for(ll i = 1; i <= 20; ++i) {
        for(ll j = 1; j <= m; ++j) {
            ll v = i * j;
            has[v] = true;
        }

        for(int j = 1; j <= 20 * m; ++j) {
            if(has[j]) num[i]++;
        }
    }


    ll res = 1;
    vector<char> finish(n + 1, false);

    for(ll i = 2; i <= n; ++i) {
        if(finish[i]) continue;

        int cnt = 1;
        for(ll cur = i * i; cur <= n; cur *= i) {
            finish[cur] = true;
            cnt++;
        }
        res += num[cnt];
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
