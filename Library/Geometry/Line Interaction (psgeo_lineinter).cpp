// num=0: no inter / num=1: has inter / num=2: inf inter
template <typename P>
P getLineInter(P a1, P a2, P b1, P b2, int& num)
{
    P a = a2 - a1, b = b2 - b1;
    auto d = a.cross(b);
    if(d == 0) {
        if(a.cross(b1 - a1) == 0) num = 2;
        else num = 0;
        return { 0, 0 };
    }
    auto p = (a2 - b1).cross(b);
    auto q = b.cross(a1 - b1);
    num = 1;
    return (a1 * p + a2 * q) / d;
}
