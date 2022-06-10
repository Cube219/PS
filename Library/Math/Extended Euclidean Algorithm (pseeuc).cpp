struct ENode
{
    ll s;
    ll t;
    ll g;
};

ENode eeuc(ll a, ll b)
{
    if(b == 0) return { 1, 0, a };

    ll r = a % b;
    auto res = eeuc(b, r);
    ll x = res.t;
    ll y = res.s - a / b * res.t;
    return { x, y, res.g };
}
// Ax+By=C, D=gcd(A, B)=g
// x0 = s * C/D       y0 = t * C/D
// s = x0 + k * B/D   t = y0 - k * A/D
