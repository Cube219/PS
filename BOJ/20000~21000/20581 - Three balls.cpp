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

template <ll mod>
struct ModInt
{
    ll v;
    ModInt(ll _v) : v((_v% mod + mod) % mod) {}

    ModInt& operator+=(const ModInt& rhs)
    {
        v = (v + rhs.v) % mod;
        return *this;
    }
    ModInt& operator-=(const ModInt& rhs)
    {
        v = (v - rhs.v + mod) % mod;
        return *this;
    }
    ModInt& operator*=(const ModInt& rhs)
    {
        v = (v * rhs.v) % mod;
        return *this;
    }
    ModInt operator+(const ModInt& rhs) const
    {
        ModInt res(*this);
        res += rhs;
        return res;
    }
    ModInt operator-(const ModInt& rhs) const
    {
        ModInt res(*this);
        res -= rhs;
        return res;
    }
    ModInt operator*(const ModInt& rhs) const
    {
        ModInt res(*this);
        res *= rhs;
        return res;
    }
};
using mint = ModInt<MOD>;

struct NCR
{
    vector<mint> f, invf;
    NCR(int n) : f(n + 1, 0), invf(n + 1, 0)
    {
        f[0] = 1;
        for(int i = 1; i <= n; ++i) f[i] = f[i - 1] * i;
        invf[n] = pw(f[n].v, MOD - 2);
        for(int i = n - 1; i >= 0; --i) invf[i] = invf[i + 1] * (i + 1);
    }

    mint pw(ll a, ll b)
    {
        mint res = 1, aa = a;
        for(; b > 0; b >>= 1) {
            if(b & 1) res *= aa;
            aa *= aa;
        }
        return res;
    }

    mint get(int n, int r)
    {
        return f[n] * invf[r] * invf[n - r];
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> r(3);
    vector<string> str(3);
    for(int i = 0; i < 3; ++i) cin >> r[i] >> str[i];

    NCR ncr(n + 1);

    mint res = 0;
    // 1개
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j <= r[i]; ++j) {
            res += ncr.get(n, j);
        }
    }

    // 2개
    auto process = [&](int i1, int i2) {
        mint rr = 0;

        int diff = 0;
        for(int i = 0; i < n; ++i) if(str[i1][i] != str[i2][i]) diff++;
        int same = n - diff;
        vector<mint> sum(same + 1, 0);
        for(int i = 0; i <= same; ++i) sum[i] = ncr.get(same, i);
        partial_sum(sum.begin(), sum.end(), sum.begin());

        for(int use1 = 0; use1 <= diff; ++use1) {
            int use2 = diff - use1;
            if(r[i1] < use1 || r[i2] < use2) continue;

            mint v1 = ncr.get(diff, use1);
            int remain = min(r[i1] - use1, r[i2] - use2);
            v1 *= sum[min(remain, same)];
            rr += v1;
        }
        return rr;
    };
    res -= process(0, 1);
    res -= process(0, 2);
    res -= process(1, 2);

    // 3개
    // 1 0 0 / 0 1 0 / 0 0 1
    int diff1 = 0, diff2 = 0, diff3 = 0;
    for(int i = 0; i < n; ++i) {
        // 1 0 0
        if(str[0][i] != str[1][i] && str[0][i] != str[2][i]) diff1++;
        // 0 1 0
        if(str[0][i] != str[1][i] && str[0][i] == str[2][i]) diff2++;
        // 0 0 1
        if(str[0][i] == str[1][i] && str[0][i] != str[2][i]) diff3++;
    }
    int same = n - diff1 - diff2 - diff3;
    if(diff3 > diff1) {
        swap(diff3, diff1);
        swap(r[2], r[0]);
    }
    if(diff3 > diff2) {
        swap(diff3, diff2);
        swap(r[2], r[1]);
    }
    vector<mint> sum(same + 1, 0);
    for(int i = 0; i <= same; ++i) sum[i] = ncr.get(same, i);
    partial_sum(sum.begin(), sum.end(), sum.begin());
    vector<vector<mint>> left(n + 1, vector<mint>(diff3 + 1, 0));
    auto right = left;
    for(int use1 = 0; use1 <= diff1; ++use1) {
        for(int use2 = 0; use2 <= diff2; ++use2) {
            int remain1 = r[0] - use1 - (diff2 - use2);
            int remain2 = r[1] - use2 - (diff1 - use1);
            int remain3 = r[2] - (diff1 - use1) - (diff2 - use2);
            if(remain1 < 0 || remain2 < 0 || remain3 < 0) continue;

            mint v1 = ncr.get(diff1, use1) * ncr.get(diff2, use2);

            int mn = min(remain1, remain2);
            int use3 = remain3 - mn + diff3;
            use3 = min(use3, diff3 * 2);
            use3 = max(0, use3);

            auto apply = [&](vector<vector<mint>>& arr) {
                int k = min(mn - (diff3 - use3), remain3 - use3);
                if(k >= 0 && 0 <= use3 && use3 <= diff3) {
                    arr[k][use3] += v1;
                }
            };
            if(use3 & 1) {
                // 고점이 2개
                use3 /= 2;
                apply(left);
                use3++;
                apply(right);
            } else {
                // 고점이 1개
                use3 /= 2;
                int top = min(mn - (diff3 - use3), remain3 - use3);
                if(top >= 0) res += v1 * ncr.get(diff3, use3) * sum[min(same, top)];

                use3--;
                apply(left);
                use3 += 2;
                apply(right);
            }
        }
    }
    
    for(int k = n; k >= 0; --k) {
        for(int use3 = 0; use3 <= diff3; ++use3) {
            mint v2 = ncr.get(diff3, use3) * sum[min(same, k)];
            mint v1 = left[k][use3] + right[k][use3];
            res += v1 * v2;

            if(k > 0) {
                if(use3 > 0) left[k - 1][use3 - 1] += left[k][use3];
                if(use3 < diff3) right[k - 1][use3 + 1] += right[k][use3];
            }
        }
    }

    cout << res.v;
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
