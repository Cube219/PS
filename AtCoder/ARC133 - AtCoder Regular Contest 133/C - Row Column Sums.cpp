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
    ll n, m;
    ll k;
    cin >> n >> m >> k;
    vector<ll> a(n), b(m);
    for(auto& v : a) cin >> v;
    for(auto& v : b) cin >> v;

    ll hmax = (k - 1) * m % k;
    ll vmax = (k - 1) * n % k;
    for(auto& v : a) {
        v = (hmax - v + k) % k;
    }
    for(auto& v : b) {
        v = (vmax - v + k) % k;
    }

    ll res = n * m * (k - 1);
    vector<ll> cnt(k, 0);
    for(auto& v : a) {
        cnt[v]++;
    }
    for(auto& v : b) {
        if(cnt[v] > 0) {
            res -= v;
        }
        cnt[v]--;
    }

    ll asum = 0;
    ll bsum = 0;
    for(int i = 0; i < k; ++i) {
        if(cnt[i] > 0) asum += (ll)cnt[i] * i;
        else bsum -= (ll)cnt[i] * i;
    }

    ll v = (asum - bsum) % k;
    v += k;
    v %= k;
    if(v != 0) {
        cout << "-1";
        return;
    }
    res -= max(asum, bsum);
    if(res < 0) res = -1;
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
