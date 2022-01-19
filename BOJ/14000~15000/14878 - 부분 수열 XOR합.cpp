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

// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastSubsetTransform.h
void FST(vector<ll>& a, bool inv)
{
    for(int n = a.size(), step = 1; step < n; step *= 2) {
        for(int i = 0; i < n; i += 2 * step) {
            for(int j = i; j < i + step; ++j) {
                ll& u = a[j], & v = a[j + step];
                tie(u, v) =
                    pair<ll, ll>(u + v, u - v);
            }
        }
    }
    if (inv) for (ll& x : a) x /= a.size();
}
vector<ll> conv(vector<ll> a, vector<ll> b)
{
    FST(a, false); FST(b, false);
    for(int i = 0; i < a.size(); ++i) a[i] *= b[i];
    FST(a, true); return a;
}

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    vector<ll> d(65536, 0);
    int cur = 0;
    for(int v : a){
        cur ^= v;
        d[cur]++;
    }
    d[0]++;

    vector<ll> d2 = d;
    auto res = conv(d, d2);

    ll mx = d[0] - n - 1, mxv = 0;
    for(int i = 1; i < 65536; ++i) {
        if(mx < res[i] / 2) {
            mx = res[i] / 2;
            mxv = i;
        }
    }

    cout << mxv << " " << mx;
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
