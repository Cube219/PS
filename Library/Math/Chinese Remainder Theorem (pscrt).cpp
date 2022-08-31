// x = a (mod m)
struct Con { ll a, m; };
Con crt(Con c1, Con c2)
{
    if(c1.m < c2.m) swap(c1, c2);
    ERes r = eeuc(c1.m, c2.m);
    if((c2.a - c1.a) % r.g) return { -1, -1 };

    Con res;
    res.m = c1.m * c2.m / r.g;
    res.a = (c2.a - c1.a) % c2.m * r.x % c2.m / r.g * c1.m + c1.a;
    if(res.a < 0) res.a += res.m;
    return res;
}
