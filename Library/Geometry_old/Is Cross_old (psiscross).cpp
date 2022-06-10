bool isCross(Point l1p1, Point l1p2, Point l2p1, Point l2p2)
{
    Point line = l1p2 - l1p1;
    Point a = l2p1 - l1p2;
    Point b = l2p2 - l1p2;
    ll cwa = ccw(line, a);
    ll cwb = ccw(line, b);
    if((cwa > 0 && cwb > 0) || (cwa < 0 && cwb < 0)) return false;
    if(cwa == 0 && cwb == 0) {
        if(l1p1.x > l1p2.x) swap(l1p1.x, l1p2.x);
        if(l1p1.y > l1p2.y) swap(l1p1.y, l1p2.y);
        if(l2p1.x > l2p2.x) swap(l2p1.x, l2p2.x);
        if(l2p1.y > l2p2.y) swap(l2p1.y, l2p2.y);

        if(l1p2.x < l2p1.x) return false;
        if(l2p2.x < l1p1.x) return false;
        if(l1p2.y < l2p1.y) return false;
        if(l2p2.y < l1p1.y) return false;

        return true;
    }

    line = l2p2 - l2p1;
    a = l1p1 - l2p2;
    b = l1p2 - l2p2;
    cwa = ccw(line, a);
    cwb = ccw(line, b);
    if((cwa > 0 && cwb > 0) || (cwa < 0 && cwb < 0)) return false;
    return true;
}
