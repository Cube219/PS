double getLineDis(Point l1, Point l2, Point p)
{
    Point l = l2 - l1;
    return (double)l.cross(p - l1) / l.dis();
}
