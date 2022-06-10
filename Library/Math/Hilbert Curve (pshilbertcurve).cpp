// https://en.wikipedia.org/wiki/Hilbert_curve
//convert (x,y) to d
int hilbertCurve(int x, int y, int n = (1 << 21))
{
    n = (1 << (n - 1));
    int rx, ry, s, d = 0;
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
