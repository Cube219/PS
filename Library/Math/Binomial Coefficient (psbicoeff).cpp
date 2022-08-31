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

    // use BiCoeff bi(mod - 1);
    ll get_lucas(ll n, ll r)
    {
        ll res = 1;
        for(; n > 0 || r > 0; n /= mod, r /= mod) {
            res = res * get(n % mod, r % mod) % mod;
        }
        return mod;
    }
};
