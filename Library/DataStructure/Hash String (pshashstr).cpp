template <ll h1 = 3137, ll m1 = 998244353, ll h2 = 53, ll m2 = 1610612741>
struct HashStr
{
    vector<ll> hv, hpow;
    vector<ll> hv2, hpow2;

    HashStr(const string& str)
    {
        int n = str.size();
        hv.resize(n);
        hpow.resize(n);

        hv[0] = str[0];
        hpow[0] = 1;
        for(int i = 1; i < n; ++i) {
            hv[i] = (hv[i - 1] * h1 + str[i]) % m1;
            hpow[i] = (hpow[i - 1] * h1) % m1;
        }

        hv2.resize(n);
        hpow2.resize(n);

        hv2[0] = str[0];
        hpow2[0] = 1;
        for(int i = 1; i < n; ++i) {
            hv2[i] = (hv2[i - 1] * h2 + str[i]) % m2;
            hpow2[i] = (hpow2[i - 1] * h2) % m2;
        }
    }

    // [l, r]
    ll substr(int l, int r)
    {
        ll res = hv[r];
        if(l > 0) {
            res -= hv[l - 1] * hpow[r - l + 1];
            res = ((res % m1) + m1) % m1;
        }
        ll res2 = hv2[r];
        if(l > 0) {
            res2 -= hv2[l - 1] * hpow2[r - l + 1];
            res2 = ((res2 % m2) + m2) % m2;
        }
        return res << 32 | res2;
    }
};
