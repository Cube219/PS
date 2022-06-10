// https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/FastSubsetTransform.h
void FST(vector<ll>& a, bool inv)
{
    for(int n = a.size(), step = 1; step < n; step *= 2) {
        for(int i = 0; i < n; i += 2 * step) {
            for(int j = i; j < i + step; ++j) {
                ll& u = a[j], & v = a[j + step];
                tie(u, v) =
                    inv ? pair<ll, ll>(v - u, u) : pair<ll, ll>(v, u + v);    // AND
                    // inv ? pair<ll, ll>(v, u - v) : pair<ll, ll>(u + v, u); // OR  /// include-line
                    pair<ll, ll>(u + v, u - v);                               // XOR /// include-line
            }
        }
    }
    // if (inv) for (ll& x : a) x /= a.size(); // XOR only /// include-line
}
vector<ll> conv(vector<ll> a, vector<ll> b)
{
    FST(a, false); FST(b, false);
    for(int i = 0; i < a.size(); ++i) a[i] *= b[i];
    FST(a, true); return a;
}
