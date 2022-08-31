pair<Point, Point> rotatingCalipers(vector<Point>& cvx)
{
    pair<Point, Point> res = { cvx[0], cvx[0] };
    int n = cvx.size(), a = 0, b = 0;
    for(int i = 0; i < n * 2; ++i) {
        if((res.first - res.second).dis2() < (cvx[a] - cvx[b]).dis2()) {
            res = { cvx[a], cvx[b] };
        }
        Point av = cvx[(a + 1) % n] - cvx[a];
        Point bv = cvx[b] - cvx[(b + 1) % n];
        if(av.cross(bv) > 0) a = (a + 1) % n;
        else b = (b + 1) % n;
    }
    return res;
}
