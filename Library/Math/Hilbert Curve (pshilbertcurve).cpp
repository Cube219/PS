// https://en.wikipedia.org/wiki/Hilbert_curve
//convert (x,y) to d
ll hilbertCurve(int x, int y, ll n)
{
    ll rx, ry, s = 1, d = 0;
    while(s < n) s *= 2;
    n = s;
    for(s = n / 2; s > 0; s /= 2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        // rotate
        if(ry == 0) {
            if(rx == 1) {
                x = n - 1 - x;
                y = n - 1 - y;
            }
            swap(x, y);
        }
    }
    return d;
}
