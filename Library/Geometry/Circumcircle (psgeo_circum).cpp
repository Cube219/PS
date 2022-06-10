template <typename P>
P getCircumcircle(P a, P b, P c)
{
    P ac = c - a, ab = b - a;
    return a + (ac * ab.dis2() - ab * ac.dis2()).perp() / ac.cross(ab) / 2;
}
