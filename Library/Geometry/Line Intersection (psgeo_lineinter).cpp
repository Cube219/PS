// 0: no inter / 1: has inter / 2: inf inter
pair<int, Point> getLineInter(Point a1, Point a2, Point b1, Point b2)
{
    Point a = a2 - a1, b = b2 - b1;
    auto d = a.cross(b);
    if(d == 0) {
        return { (a.cross(b1 - a1) == 0 ? 2 : 0), { 0, 0 } };
    }
    auto p = (a2 - b1).cross(b);
    auto q = b.cross(a1 - b1);
    return { 1, (a1 * p + a2 * q) / d };
}
