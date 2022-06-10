// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/BerlekampMassey.h
// usage: ({0, 1, 1, 3, 5, 11}) // {1, 2}
template <ll mod = 998244353>
struct BerlekampMassey
{
    ll modpow(ll b, ll e)
    {
        ll ans = 1;
        for(; e; b = b * b % mod, e /= 2) if(e & 1) ans = ans * b % mod;
        return ans;
    }

    vector<ll> get(vector<ll> s)
    {
        int n = s.size(), L = 0, m = 0;
        vector<ll> C(n), B(n), T;
        C[0] = B[0] = 1;

        ll b = 1;
        for(int i = 0; i < n; ++i) {
            ++m;
            ll d = s[i] % mod;
            for(int j = 1; j < L + 1; ++j) {
                d = (d + C[j] * s[i - j]) % mod;
            }
            if(!d) continue;
            T = C;
            ll coef = d * modpow(b, mod - 2) % mod;
            for(int j = m; j < n; ++j) {
                C[j] = (C[j] - coef * B[j - m]) % mod;
            }
            if(2 * L > i) continue;
            L = i + 1 - L;
            B = T;
            b = d;
            m = 0;
        }

        C.resize(L + 1);
        C.erase(C.begin());
        for(ll& x : C) x = (mod - x) % mod;
        return C;
    }
};
