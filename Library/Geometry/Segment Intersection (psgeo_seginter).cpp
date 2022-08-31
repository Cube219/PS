vector<Point> getSegInter(Point a1, Point a2, Point b1, Point b2)
{
    Point a = a2 - a1, b = b2 - b1;
    auto ab1 = a.cross(b1 - a1), ab2 = a.cross(b2 - a1);
    auto ba1 = b.cross(a1 - b1), ba2 = b.cross(a2 - b1);
    auto sgn = [](auto x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); };
    if(sgn(ab1) * sgn(ab2) < 0 && sgn(ba1) * sgn(ba2) < 0) {
        return { (a1 * ba2 - a2 * ba1) / (ba2 - ba1) };
    }
    set<Point> s;
    if(isOnSeg(a1, a2, b1)) s.insert(b1);
    if(isOnSeg(a1, a2, b2)) s.insert(b2);
    if(isOnSeg(b1, b2, a1)) s.insert(a1);
    if(isOnSeg(b1, b2, a2)) s.insert(a2);
    return { s.begin(), s.end() };
}
