template <ll h1 = 3137, ll m1 = 998244353, ll h2 = 53, ll m2 = 1610612741>
struct HashStr
{
    vector<ll> v1, pw1, v2, pw2;

    HashStr(const string& str)
    {
        int n = str.size();
        v1.resize(n); pw1.resize(n);
        v2.resize(n); pw2.resize(n);
        v1[0] = v2[0] = str[0];
        pw1[0] = pw2[0] = 1;
        for(int i = 1; i < n; ++i) {
            v1[i] = (v1[i - 1] * h1 + str[i]) % m1;
            pw1[i] = pw1[i - 1] * h1 % m1;
            v2[i] = (v2[i - 1] * h2 + str[i]) % m2;
            pw2[i] = pw2[i - 1] * h2 % m2;
        }
    }

    // [l, r]
    ll substr(int l, int r)
    {
        ll res1 = v1[r], res2 = v2[r];
        if(l > 0) {
            ll t = v1[l - 1] * pw1[r - l + 1] % m1;
            res1 = (res1 - t + m1) % m1;
            t = v2[l - 1] * pw2[r - l + 1] % m2;
            res2 = (res2 - t + m2) % m2;
        }
        return res1 << 32 | res2;
    }
};
