bool isOnSeg(Point s1, Point s2, Point p)
{
    return (s2 - s1).cross(p - s1) == 0 && (p - s1).dot(p - s2) <= 0;
    // return getSegDis(s1, s2, p) < eps; // Use if double
}
