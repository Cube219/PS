template <typename P>
double getLineDis(P a1, P a2, P p)
{
    Point a = a2 - a1;
    return a.cross(p - a1) / a.dis();
}
