template <typename P>
vector<P> convexHull(vector<P>& poly, bool erase = false)
{
    // line 위 포함 => while 안 cross 등호 빼고, 일자인 경우 예외처리
    if(poly.size() <= 1) {
        auto newPoly = poly;
        if(erase) poly.clear();
        return newPoly;
    }

    vector<int> eraseIdx;

    sort(poly.begin(), poly.end());
    vector<P> up;
    for(int i = 0; i < poly.size(); ++i) {
        int sz = up.size();
        auto& p = poly[i];
        while(sz >= 2 && cross(up[sz - 1] - up[sz - 2], p - up[sz - 2]) <= 0) {
            up.pop_back();
            eraseIdx.pop_back();
            sz--;
        }
        up.push_back(p);
        eraseIdx.push_back(i);
    }

    vector<P> lo;
    for(int i = poly.size() - 1; i >= 0; --i) {
        int sz = lo.size();
        auto& p = poly[i];
        while(sz >= 2 && cross(lo[sz - 1] - lo[sz - 2], p - lo[sz - 2]) <= 0) {
            lo.pop_back();
            eraseIdx.pop_back();
            sz--;
        }
        lo.push_back(p);
        eraseIdx.push_back(i);
    }

    if(erase) {
        sort(eraseIdx.begin(), eraseIdx.end());
        eraseIdx.push_back(poly.size());
        vector<P> newPoly;
        int ei = 0;
        for(int i = 0; i < poly.size(); ++i) {
            while(eraseIdx[ei] < i) ei++;
            if(eraseIdx[ei] == i) ei++;
            else newPoly.push_back(poly[i]);
        }

        poly = newPoly;
    }

    up.insert(up.end(), lo.begin() + 1, lo.end() - 1);
    return up;
}
