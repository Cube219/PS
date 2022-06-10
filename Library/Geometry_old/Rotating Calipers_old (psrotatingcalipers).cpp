ll rotatingCalipers(vector<Point>& cvh)
{
    ll res = 0;
    int cvhn = cvh.size();

    int aidx = 0, bidx = 0;
    for(int i = 1; i < cvhn; ++i) {
        ll l = lensq(cvh[0], cvh[i]);
        if(res < l) {
            res = l;
            bidx = i;
        }
    }
    for(int i = 0; i < cvhn; ++i) {
        ll l = lensq(cvh[aidx], cvh[bidx]);
        if(res < l) {
            res = l;
        }
        Point av = cvh[(aidx + 1) % cvhn] - cvh[aidx];
        Point bv = cvh[(bidx + 1) % cvhn] - cvh[bidx];
        bv.x = -bv.x;
        bv.y = -bv.y;
        if(ccw(av, bv) > 0) {
            aidx++;
            aidx %= cvhn;
        } else {
            bidx++;
            bidx %= cvhn;
        }
    }

    return res;
}
