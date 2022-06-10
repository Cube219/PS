bool isInPolygon(vector<Point>& pol, Point p)
{
    if(pol.size() == 1) return false;
    else if(pol.size() == 2) return isInLine(pol[0], pol[1], p);

    for(int i = 1; i < pol.size(); ++i) {
        Point cur = pol[i - 1];
        Point nxt = pol[i];
        Point l1 = nxt - cur;
        Point l2 = p - cur;
        ll cw = ccw(l1, l2);
        if(cw == 0) {
            if(isInLine(nxt, cur, p) == true) return true;
            else return false;
        } else if(cw < 0) {
            return false;
        }
    }

    return true;
}
