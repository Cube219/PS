double getSegDis(Point s1, Point s2, Point p)
{
    if(s1 == s2) return (p - s1).dis();
    Point s = s2 - s1;
    auto t = s.dot(p - s1);
    if(0 <= t && t <= s.dis2()) {
        double c = (p - s1).dis2();
        double b = (double)t * t / s.dis2();
        return sqrt(c - b);
    } else return min((p - s1).dis(), (p - s2).dis());
}
