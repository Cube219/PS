#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'003;

// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransform.h
// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastFourierTransformMod.h
struct FFT
{
    using cpx = complex<double>;

    void fft(vector<cpx>& a)
    {
        int n = a.size(), L = 0;
        while(n > 1) {
            n >>= 1;
            L++;
        }
        n = a.size();
        static vector<complex<long double>> R(2, 1);
        static vector<cpx> rt(2, 1); // (^ 10% faster if double)
        for(static int k = 2; k < n; k *= 2) {
            R.resize(n);
            rt.resize(n);
            auto x = polar(1.0L, acos(-1.0L) / k);
            for(int i = k; i < 2 * k; ++i) {
                rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
            }
        }
        vector<int> rev(n);
        for(int i = 0; i < n; ++i) {
            rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        }
        for(int i = 0; i < n; ++i) {
            if(i < rev[i]) swap(a[i], a[rev[i]]);
        }
        for(int k = 1; k < n; k *= 2)
            for(int i = 0; i < n; i += 2 * k) {
                for(int j = 0; j < k; ++j) {
                    cpx z = rt[j + k] * a[i + j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
            }
    }

    vector<ll> conv(const vector<ll>& a, const vector<ll>& b)
    {
        if(a.empty() || b.empty()) return {};
        vector<ll> res(a.size() + b.size() - 1);
        int L = 0, n = 1;
        while(n <= res.size()) {
            n <<= 1;
            L++;
        }

        vector<cpx> in(n), out(n);
        copy(a.begin(), a.end(), begin(in));
        for(int i = 0; i < b.size(); ++i) {
            in[i].imag(b[i]);
        }
        fft(in);
        for(cpx& x : in) x *= x;
        for(int i = 0; i < n; ++i) {
            out[i] = in[-i & (n - 1)] - conj(in[i]);
        }
        fft(out);
        for(int i = 0; i < res.size(); ++i) {
            res[i] = llround(imag(out[i]) / (4 * n));
        }
        return res;
    }

    vector<ll> convmod(const vector<ll>& a, const vector<ll>& b, int mod)
    {
        if(a.empty() || b.empty()) return {};
        vector<ll> res(a.size() + b.size() - 1);
        int B = 0, n = 1, cut = (int)sqrt(mod);
        while(n <= res.size()) {
            n <<= 1;
            B++;
        }
        vector<cpx> L(n), R(n), outs(n), outl(n);
        for(int i = 0; i < a.size(); ++i) {
            L[i] = cpx((int)a[i] / cut, (int)a[i] % cut);
        }
        for(int i = 0; i < b.size(); ++i) {
            R[i] = cpx((int)b[i] / cut, (int)b[i] % cut);
        }
        fft(L);
        fft(R);
        for(int i = 0; i < n; ++i) {
            int j = -i & (n - 1);
            outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
            outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
        }
        fft(outl);
        fft(outs);
        for(int i = 0; i < res.size(); ++i) {
            ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
            ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
            res[i] = ((av % mod * cut + bv) % mod * cut + cv) % mod;
        }
        return res;
    }
};

template <int mod>
struct BiCoeff
{
    vector<int> fact, invfact;

    ll pw(ll a, ll b)
    {
        ll res = 1;
        while(b > 0) {
            if(b & 1) {
                res = res * a % mod;
            }
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }

    void init(int n)
    {
        fact.resize(n + 1);
        invfact.resize(n + 1);

        fact[0] = 1;
        for(int i = 1; i <= n; ++i) fact[i] = (ll)fact[i - 1] * i % mod;
        invfact[n] = pw(fact[n], mod - 2);
        for(int i = n - 1; i >= 0; --i) invfact[i] = (ll)invfact[i + 1] * (i + 1) % mod;
    }

    ll get(int n, int r)
    {
        if(n < r) return 0;
        ll factn = fact[n];
        ll factrnr = (ll)fact[r] * (ll)fact[n - r] % mod;
        return factn * pw(factrnr, mod - 2) % mod;
    }
};

void solve()
{
    int n, k, r;
    cin >> n >> k >> r;
    vector<int> cnt(r, 0);
    for(int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        cnt[v % r]++;
    }

    BiCoeff<MOD> bi;
    bi.init(1000001);
    FFT fft;

    vector<vector<int>> dp(r, vector<int>(k + 1, 0));
    dp[0][0] = 1;
    for(int remain = 0; remain < r; ++remain) {
        vector<vector<int>> ndp(r, vector<int>(k + 1, 0));

        vector<ll> way(k + 1);
        for(int i = 0; i < k + 1; ++i) {
            way[i] = bi.get(cnt[remain], i);
        }

        for(int st = 0; st < r; ++st) {
            vector<ll> d(k + 1);
            for(int i = 0; i < k + 1; ++i) {
                d[i] = dp[(st + remain * i) % r][i];
            }

            auto res = fft.convmod(d, way, MOD);

            for(int i = 0; i < k + 1; ++i) {
                ndp[(st + remain * i) % r][i] = ((ll)ndp[(st + remain * i) % r][i] + res[i]) % MOD;
            }
        }

        swap(dp, ndp);
    }

    cout << dp[0][k];
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
