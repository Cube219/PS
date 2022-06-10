template <int mod>
struct BiCoeff_Lucas
{
    vector<ll> fact, invfact;

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

    // O(mod)
    void init()
    {
        int n = mod - 1;
        fact.resize(n);
        invfact.resize(n);

        fact[0] = 1;
        for(int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % mod;
        invfact[n] = pw(fact[n], mod - 2);
        for(int i = n - 1; i >= 0; --i) invfact[i] = invfact[i + 1] * (i + 1) % mod;
    }

    ll ncr(int n, int r)
    {
        if(n < r) return 0;
        ll factn = fact[n];
        ll invrnr = invfact[r] * invfact[n - r] % mod;
        return factn * invrnr % mod;
    }

    // O(logn + logr), Only use when MOD is prime
    ll get(ll n, ll r)
    {
        ll res = 1;
        while(n > 0 || r > 0) {
            ll a = n % mod;
            ll b = r % mod;
            res *= ncr(a, b);
            res %= mod;

            n /= mod;
            r /= mod;
        }
        return res;
    }
};
