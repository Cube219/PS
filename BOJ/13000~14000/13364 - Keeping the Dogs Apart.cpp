#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

using ll = long long int;

struct Point
{
    int x, y;
};
struct DPoint
{
    double x, y;
};

int n, m;
Point a[100001], b[100001];
double res = 20001;

double dis(DPoint a, DPoint b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a[i] = { x, y };
    }
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        b[i] = { x, y };
    }

    int aidx = 0, bidx = 0;
    double at = 0, bt = 0;
    while(aidx < n - 1 && bidx < m - 1) {
        Point dai = { a[aidx + 1].x - a[aidx].x, a[aidx + 1].y - a[aidx].y };
        double lena = sqrt((double)(dai.x * dai.x + dai.y * dai.y));
        Point dbi = { b[bidx + 1].x - b[bidx].x, b[bidx + 1].y - b[bidx].y };
        double lenb = sqrt((double)(dbi.x * dbi.x + dbi.y * dbi.y));
        DPoint da = { (double)dai.x / lena, (double)dai.y / lena };
        DPoint db = { (double)dbi.x / lenb, (double)dbi.y / lenb };

        DPoint cura = { a[aidx].x + da.x * at, a[aidx].y + da.y * at };
        DPoint curb = { b[bidx].x + db.x * bt, b[bidx].y + db.y * bt };
        // 시작 지점
        res = min(res, dis(cura, curb));

        lena -= at;
        lenb -= bt;

        // 중간 지점
        DPoint p = { cura.x - curb.x, cura.y - curb.y };
        DPoint q = { da.x - db.x, da.y - db.y };
        double t = -(p.x * q.x + p.y * q.y) / (q.x * q.x + q.y * q.y);
        if(t > 0 && t < min(lena, lenb)) {
            DPoint newa;
            DPoint newb;
            newa = { cura.x + da.x * t, cura.y + da.y * t };
            newb = { curb.x + db.x * t, curb.y + db.y * t };
            res = min(res, dis(newa, newb));
        }

        // 끝 지점
        if(lena < lenb) {
            cura = { (double)a[aidx + 1].x, (double)a[aidx + 1].y };
            curb = { curb.x + db.x * lena, curb.y + db.y * lena };
            res = min(res, dis(cura, curb));
            aidx++;
            at = 0;
            bt += lena;
        } else {
            cura = { cura.x + da.x * lenb, cura.y + da.y * lenb };
            curb = { (double)b[bidx + 1].x, (double)b[bidx + 1].y };
            res = min(res, dis(cura, curb));
            bidx++;
            at += lenb;
            bt = 0;
        }
    }

    cout.precision(15);
    cout << res;

    return 0;
}
