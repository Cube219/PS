struct CRT
{
    // x = v (mod m)
    struct Con
    {
        ll v, m;
    };

    Con get(Con c1, Con c2)
    {
        if(c1.m < c2.m) swap(c1, c2);
        ENode en = eeuc(c1.m, c2.m);
        if((c1.v - c2.v) % en.g != 0) return { -1, -1 };

        ll c = (c2.v - c1.v) % c2.m;
        if(c < 0) c += c2.m;

        ll resm = c1.m * c2.m / en.g;
        ll resv = (en.s * c) % c2.m / en.g * c1.m + c1.v;
        resv %= resm;
        if(resv < 0) resv += resm;
        return { resv, resm };
    }
};
