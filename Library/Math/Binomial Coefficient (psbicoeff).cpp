template <int mod>
struct BiCoeff
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

    void init(int n)
    {
        fact.resize(n + 1);
        invfact.resize(n + 1);

        fact[0] = 1;
        for(int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % mod;
        invfact[n] = pw(fact[n], mod - 2);
        for(int i = n - 1; i >= 0; --i) invfact[i] = invfact[i + 1] * (i + 1) % mod;
    }

    ll get(int n, int r)
    {
        return fact[n] * (invfact[r] * invfact[n - r] % mod) % mod;
        // return fact[n] * pw(fact[r] * fact[n - r] % mod, mod - 2) % mod;
    }
};
