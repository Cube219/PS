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

vector<vector<ll>> res(21, vector<ll>(2, 0));

template <ll mod>
struct BiCoeff
{
    vector<ll> f, invf;
    BiCoeff(int n) : f(n + 1), invf(n + 1)
    {
        f[0] = 1;
        for(int i = 1; i <= n; ++i) f[i] = f[i - 1] * i % mod;
        auto pw = [](ll a, ll b) {
            ll res = 1;
            for(; b > 0; b >>= 1, a = a * a % mod) if(b & 1) res = res * a % mod;
            return res;
        };
        invf[n] = pw(f[n], mod - 2);
        for(int i = n - 1; i >= 0; --i) invf[i] = invf[i + 1] * (i + 1) % mod;
    }

    ll get(int n, int r)
    {
        return f[n] * (invf[r] * invf[n - r] % mod) % mod;
    }
};

void init()
{
    BiCoeff<MOD> bi(100);
    res[0][0] = res[0][1] = 1;
    res[1][0] = res[1][1] = 1;
    for(int i = 2; i <= 20; ++i) {
        for(int j = 0; j < i; ++j) {
            ll lcnt = res[j][j & 1];
            ll rcnt = res[i - j - 1][1];
            ll c = bi.get(i - 1, j);
            res[i][j & 1] += lcnt * rcnt * c;
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    if(n == 1) cout << "1\n";
    else cout << res[n][0] + res[n][1] << "\n";
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    init();

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
