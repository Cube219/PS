double getSegDis(Point s1, Point s2, Point p)
{
    if(s1 == s2) return (p - s1).dis();
    Point s = s2 - s1;
    Point sp = p - s1;
    auto d = s.dis2();
    auto t = min(d, max(0.0, sp.dot(s)));
    return (sp * d - s * t).dis() / d;
}
