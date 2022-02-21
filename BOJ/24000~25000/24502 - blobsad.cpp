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
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    ll sum = 0;
    for(auto& v : a) {
        cin >> v;
        sum += v;
    }
    if(sum % k != 0) {
        cout << "blobsad";
        return;
    }

    vector<ll> d(n), pre(n), suf(n);
    // ll cur = 0;
    // for(int i = 0; i < n; ++i) {
    //     // res -= a[i] * i;
    //     if(a[i] % k == 0) continue;
    //
    //     ll remove = a[i] - ((a[i] / k) * k);
    //     ll add = (a[i] / k + 1) * k - a[i];
    //     d[i] = min(remove, add);
    //     cur += d[i] * i;
    // }

    ll res = 0;
    for(int i = 0; i < n - 1; ++i) {
        if(a[i] % k == 0) continue;

        ll remove = a[i] - ((a[i] / k) * k);
        ll add = (a[i] / k + 1) * k - a[i];
        if(a[i] < 0) {
            remove = k + 1;
            add = -a[i];
        }
        if(add < remove) {
            res += add;
            a[i] += add;
            a[i + 1] -= add;
        } else {
            res += remove;
            a[i] -= remove;
            a[i + 1] += remove;
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
