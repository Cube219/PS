// idea: https://rkm0959.tistory.com/182
template <int p, int e>
struct BiCoeff_PrimePower
{
    vector<ll> val;
    ll pe;

    // O(p^e)
    void init()
    {
        pe = 1;
        for(int i = 0; i < e; i++) pe *= p;

        val.resize(pe);
        val[0] = 1;
        val[1] = 1;
        for(int i = 2; i < pe; ++i) {
            val[i] = val[i - 1];
            if(i % p == 0) continue;
            val[i] *= i;
            val[i] %= pe;
        }
    }

    // n! = p^k * r  ->  { k, r (mod p^e)  }
    pair<int, ll> getnfact(ll n)
    {
        if(n < p) {
            return { 0, val[n] };
        }

        pair<int, ll> res;

        ll div = n / p;
        res.first = div;

        auto r = getnfact(div);

        ll div2 = n / pe;
        ll remain2 = n % pe;

        res.second = val[remain2];

        if(div2 % 2 == 1) {
            res.second = (res.second * val[pe - 1]) % pe;
        }

        res.first += r.first;
        res.second = (res.second * r.second) % pe;
        return res;
    }

    ll invmod(ll a)
    {
        ENode res = eeuc(a, pe);
        ll r = res.s % pe;
        if(r < 0) r += pe;
        return r;
    }

    // O(logn)
    ll get(ll n, ll r)
    {
        auto nres = getnfact(n);
        auto rres = getnfact(r);
        auto nrres = getnfact(n - r);

        int pnum = nres.first - rres.first - nrres.first;
        ll remain = (nres.second * invmod((rres.second * nrres.second) % pe)) % pe;
        if(pnum >= e) {
            return 0;
        }
        for(int i = 0; i < pnum; ++i) {
            remain *= p;
            remain %= pe;
        }
        return remain;
    }
};
