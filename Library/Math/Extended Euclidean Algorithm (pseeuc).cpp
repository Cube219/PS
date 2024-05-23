struct ERes { ll x, y, g; };
ERes eeuc(ll a, ll b)
{
    if(b == 0) return { 1, 0, a };

    ERes res = eeuc(b, a % b);
    ll x = res.y;
    ll y = res.x - a / b * res.y;
    return { x, y, res.g };
}
// Ax+By=C, D=gcd(A,B)=g
// x0 = x * C/D       y0 = y * C/D
// s = x0 + k*B/D   t = y0 - k*A/D   (k=임의의 정수)
