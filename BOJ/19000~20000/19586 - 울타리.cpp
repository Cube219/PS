#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

struct Point
{
    ll x, y;
};

Point operator+(const Point& l, const Point& r)
{
    return { l.x + r.x, l.y + r.y };
}

Point operator-(const Point& l, const Point& r)
{
    return { l.x - r.x, l.y - r.y };
}

ll dot(const Point& l, const Point& r)
{
    return l.x * r.x + l.y * r.y;
}

ll ccw(Point l1, Point l2)
{
    return l1.x * l2.y - l2.x * l1.y;
}

ll lensq(Point& a, Point& b)
{
    ll dx = abs(a.x - b.x);
    ll dy = abs(a.y - b.y);
    return dx * dx + dy * dy;
}

void convexHull(vector<Point>& p, vector<Point>& st, bool erase = false)
{
    if(p.size() <= 2) {
        st.assign(p.begin(), p.end());
        if(erase == true) p.clear();
        return;
    }

    sort(p.begin(), p.end(), [](const Point& l, const Point& r) {
        if(l.y == r.y) return l.x > r.x;
        return l.y > r.y;
    });
    Point pivot = p.back();
    p.pop_back();
    sort(p.begin(), p.end(), [pivot](const Point& l, const Point& r) {
        Point l1 = l - pivot;
        Point l2 = r - pivot;
        ll cw = ccw(l1, l2);
        if(cw == 0) {
            if(l1.y == l2.y) return l1.x < l2.x;
            return l1.y < l2.y;
        } else if(cw > 0) return true;
        else return false;
    });
    st.push_back(pivot);
    st.push_back(p[0]);
    vector<int> eraseIdx;
    eraseIdx.push_back(0);
    for(int i = 1; i < p.size(); ++i) {
        if(st.size() < 2) {
            st.push_back(p[i]);
            eraseIdx.push_back(i);
            continue;
        }
        Point p2 = p[i];
        Point p1 = st[st.size() - 1];
        Point p0 = st[st.size() - 2];

        Point l1 = p1 - p0;
        Point l2 = p2 - p0;
        ll cw = ccw(l1, l2);
        if(cw > 0) {
            st.push_back(p[i]);
            eraseIdx.push_back(i);
        } else {
            st.pop_back();
            eraseIdx.pop_back();
            i--;
        }
    }
    if(erase == true) {
        sort(eraseIdx.begin(), eraseIdx.end());
        eraseIdx.push_back(-1);
        int ei = 0;
        vector<Point> newp;
        for(int i = 0; i < p.size(); ++i) {
            if(i == eraseIdx[ei]) {
                ei++;
            } else {
                newp.push_back(p[i]);
            }
        }
        p.clear();
        p.assign(newp.begin(), newp.end());
    } else {
        p.push_back(pivot);
    }
}

double rotatingCalipers(vector<Point>& cvh)
{
    if(cvh.size() == 1) return 0.0;
    if(cvh.size() == 2) {
        return sqrt(lensq(cvh[0], cvh[1])) * 2;
    }

    double res = 99999999999999.0;
    ll mxl = 0;
    int cvhn = cvh.size();

    int idx[4] = { 0, 0, 0, 0 };
    Point v = cvh[0];
    for(int i = 1; i < cvhn; ++i) {
        if((v.x > cvh[i].x) || (v.x == cvh[i].x && v.y > cvh[i].y)) {
            idx[0] = i;
            v = cvh[i];
        }
    }
    v = cvh[0];
    for(int i = 1; i < cvhn; ++i) {
        if(v.y > cvh[i].y || (v.y == cvh[i].y && v.x < cvh[i].x)) {
            idx[1] = i;
            v = cvh[i];
        }
    }
    v = cvh[0];
    for(int i = 1; i < cvhn; ++i) {
        if(v.x < cvh[i].x || (v.x == cvh[i].x && v.y < cvh[i].y)) {
            idx[2] = i;
            v = cvh[i];
        }
    }
    v = cvh[0];
    for(int i = 1; i < cvhn; ++i) {
        if(v.y < cvh[i].y || (v.y == cvh[i].y && v.x > cvh[i].x)) {
            idx[3] = i;
            v = cvh[i];
        }
    }

    for(int i = 0; i < cvhn; ++i) {
        Point lvec = cvh[(idx[0] + 1) % cvhn] - cvh[idx[0]];
        Point rvec = cvh[idx[2]] - cvh[(idx[2] + 1) % cvhn];
        Point uvec = cvh[idx[3]] - cvh[(idx[3] + 1) % cvhn];
        Point dvec = cvh[(idx[1] + 1) % cvhn] - cvh[idx[1]];

        Point min1, min2;
        int min1idx, min2idx;

        if(ccw(lvec, rvec) > 0) {
            min1 = lvec;
            min1idx = 0;
        } else {
            min1 = rvec;
            min1idx = 2;
        }
        if(ccw(uvec, dvec) > 0) {
            min2 = uvec;
            min2idx = 3;
        } else {
            min2 = dvec;
            min2idx = 1;
        }
        Point tmp = min2;
        min2.x = tmp.y;
        min2.y = -tmp.x;
        if(ccw(min1, min2) < 0) {
            min1 = min2;
            min1idx = min2idx;
        }
        while(idx[(min1idx + 1) % 4] == idx[min1idx]) {
            min1idx++;
            min1idx %= 4;
        }

        Point f1 = cvh[idx[min1idx]];
        Point f2 = cvh[(idx[min1idx] + 1) % cvhn];
        Point rp = cvh[idx[(min1idx + 1) % 4]];
        Point lp = cvh[idx[(min1idx + 3) % 4]];
        double f12 = sqrt(lensq(f1, f2));
        double w = f12;
        double nx = (double)(f2.x - f1.x) / w;
        double ny = (double)(f2.y - f1.y) / w;
        Point t1 = rp - f2;
        w += nx * t1.x + ny * t1.y;
        t1 = lp - f1;
        w -= nx * t1.x + ny * t1.y;

        double h = 0;
        Point p = cvh[idx[(min1idx + 2) % 4]];
        ll area = ccw(f1 - p, f2 - p);
        h = (double)area / f12;

        res = min(res, (w + h) * 2);

        idx[min1idx]++;
        idx[min1idx] %= cvhn;
        // cout << res << "\n";
    }

    return res;
}

int n;
vector<Point> d;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        ll a, b;
        cin >> a >> b;
        d.push_back({ a, b });
    }

    vector<Point> cvh;
    convexHull(d, cvh);

    cout << fixed << rotatingCalipers(cvh);

    return 0;
}
