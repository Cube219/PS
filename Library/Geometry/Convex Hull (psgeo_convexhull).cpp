vector<Point> getConvexHull(vector<Point> poly)
{
    // line 위 포함 => while 안 cross 등호 빼고, 일자인 경우 예외처리
    if(poly.size() <= 1) return poly;
    sort(poly.begin(), poly.end());

    vector<Point> lo;
    for(int i = 0; i < poly.size(); ++i) {
        int sz = lo.size();
        auto p = poly[i];
        while(sz >= 2 && cross(lo[sz - 1] - lo[sz - 2], p - lo[sz - 2]) <= 0) {
            lo.pop_back(); sz--;
        }
        lo.push_back(p);
    }
    vector<Point> hi;
    for(int i = poly.size() - 1; i >= 0; --i) {
        int sz = hi.size();
        auto p = poly[i];
        while(sz >= 2 && cross(hi[sz - 1] - hi[sz - 2], p - hi[sz - 2]) <= 0) {
            hi.pop_back(); sz--;
        }
        hi.push_back(p);
    }

    lo.insert(lo.end(), hi.begin() + 1, hi.end() - 1);
    return lo;
}
