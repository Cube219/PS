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
constexpr ll MOD = 1'000'000'007;

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

void solve()
{
    int n;
    cin >> n;
    vector<int> d(n);
    for(auto& v : d) cin >> v;

    FFT fft;
    auto dnc = [&](auto&& self, int l, int r) -> vector<ll> {
        if(l == r) return { 1, d[l] };
        int m = (l + r) / 2;

        auto lres = self(self, l, m);
        auto rres = self(self, m + 1, r);
        auto res = fft.conv(lres, rres);
        for(auto& v : res) v %= 100003;
        return res;
    };

    auto res = dnc(dnc, 0, n - 1);

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int v;
        cin >> v;
        cout << res[v] << "\n";
    }
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
