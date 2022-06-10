// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/NumberTheoreticTransform.h
template <int MOD, int ROOT>
struct NTT
{
    ll modpow(ll a, ll b)
    {
        ll res = 1;
        ll p = a;
        while(b > 0) {
            if(b & 1) {
                res = (res * p) % MOD;
            }
            p = (p * p) % MOD;
            b >>= 1;
        }
        return res;
    }

    void ntt(vector<ll>& a)
    {
        int n = a.size(), L = 0;
        while(n > 1) {
            n >>= 1;
            L++;
        }
        n = a.size();
        static vector<ll> rt(2, 1);
        for(static int k = 2, s = 2; k < n; k *= 2, s++) {
            rt.resize(n);
            ll z[] = { 1, modpow(ROOT, MOD >> s) };
            for(int i = k; i < 2 * k; ++i) {
                rt[i] = rt[i / 2] * z[i & 1] % MOD;
            }
        }
        vector<int> rev(n);
        for(int i = 0; i < n; ++i) {
            rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
        }
        for(int i = 0; i < n; ++i) {
            if(i < rev[i]) swap(a[i], a[rev[i]]);
        }
        for(int k = 1; k < n; k *= 2) {
            for(int i = 0; i < n; i += 2 * k) {
                for(int j = 0; j < k; ++j) {
                    ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
                    a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                    ai += (ai + z >= MOD ? z - MOD : z);
                }
            }
        }
    }

    vector<ll> conv(const vector<ll>& a, const vector<ll>& b)
    {
        if(a.empty() || b.empty()) return {};
        int s = a.size() + b.size() - 1;
        int B = 0, n = 1;
        while(n <= s) {
            n <<= 1;
            B++;
        }
        ll inv = modpow(n, MOD - 2);
        vector<ll> L(a), R(b), out(n);
        L.resize(n), R.resize(n);
        ntt(L), ntt(R);
        for(int i = 0; i < n; ++i) {
            out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
        }
        ntt(out);
        return { out.begin(), out.begin() + s };
    }
};

// NTT<998244353, 62> ntt;
// NTT<998244353, 3> ntt;
// NTT<167772161, 3> ntt;
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
