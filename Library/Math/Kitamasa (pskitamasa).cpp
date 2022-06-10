// https://gist.github.com/koosaga/d4afc4434dbaa348d5bef0d60ac36aa4#file-berlekamp_massey-cpp-L43
template <ll mod = 998244353>
struct Kitamasa
{
    int get_nth(const vector<ll>& rec, const vector<ll>& dp, ll n)
    {
        int m = rec.size();
        vector<ll> s(m), t(m);
        s[0] = 1;
        if(m != 1) t[1] = 1;
        else t[0] = rec[0];
        auto mul = [&rec](const vector<ll>& v, const vector<ll>& w) {
            int m = v.size();
            vector<ll> t(2 * m);
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < m; k++) {
                    t[j + k] += 1ll * v[j] * w[k] % mod;
                    if(t[j + k] >= mod) t[j + k] -= mod;
                }
            }
            for(int j = 2 * m - 1; j >= m; j--) {
                for(int k = 1; k <= m; k++) {
                    t[j - k] += 1ll * t[j] * rec[k - 1] % mod;
                    if(t[j - k] >= mod) t[j - k] -= mod;
                }
            }
            t.resize(m);
            return t;
        };
        while(n) {
            if(n & 1) s = mul(s, t);
            t = mul(t, t);
            n >>= 1;
        }
        ll ret = 0;
        for(int i = 0; i < m; i++) ret += 1ll * s[i] * dp[i] % mod;
        return ret % mod;
    }
};
// ex) a_i = a_{i-1} + 2*a_{i-2} / a_0 = 1, a_1 = 3
//     res = ki.get_nth({ 1, 2 }, { 1, 3 }, n);
