bool isInLine(Point lp1, Point lp2, Point p)
{
    Point l1 = lp2 - lp1;
    Point l2 = p - lp1;
    ll cw = ccw(l1, l2);
    if(cw != 0) return false;
    else {
        ll dt, dt2;
        if(lp1.x == lp2.x) {
            dt = abs(lp1.y - lp2.y);
            dt2 = max(abs(p.y - lp1.y), abs(p.y - lp2.y));
        } else {
            dt = abs(lp1.x - lp2.x);
            dt2 = max(abs(p.x - lp1.x), abs(p.x - lp2.x));
        }
        if(dt < dt2) return false;
        else return true;
    }
}
