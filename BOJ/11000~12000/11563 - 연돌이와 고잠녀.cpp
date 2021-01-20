#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <math.h>
using namespace std;

using ll = long long int;

double ccw(double x1, double y1, double x2, double y2)
{
    return x1 * y2 - x2 * y1;
}

int n, m;

double res = 987654321;

struct Line
{
    double x1;
    double y1;
    double x2;
    double y2;
};

Line al[2001], bl[2001];

bool canPerpen(Line l, double x, double y, double& res)
{
    double lineX = l.x2 - l.x1;
    double lineY = l.y2 - l.y1;
    double dotX = x - l.x1;
    double dotY = y - l.y1;
    double c1 = lineX * dotX + lineY * dotY;

    lineX = -lineX;
    lineY = -lineY;
    dotX = x - l.x2;
    dotY = y - l.y2;
    double c2 = lineX * dotX + lineY * dotY;
    if(c1 > 0 && c2 > 0) {
        double tSize = abs(ccw(l.x1 - x, l.y1 - y, l.x2 - x, l.y2 - y));
        double dx = l.x2 - l.x1;
        double dy = l.y2 - l.y1;
        res = tSize / sqrt(dx * dx + dy * dy);

        return true;
    } else {
        return false;
    }
}

double dis(Line l1, Line l2)
{
    double r = 987654321;

    double dx = l1.x1 - l2.x1;
    double dy = l1.y1 - l2.y1;
    double d = sqrt(dx * dx + dy * dy);
    if(r > d) r = d;
    dx = l1.x1 - l2.x2;
    dy = l1.y1 - l2.y2;
    d = sqrt(dx * dx + dy * dy);
    if(r > d) r = d;
    dx = l1.x2 - l2.x1;
    dy = l1.y2 - l2.y1;
    d = sqrt(dx * dx + dy * dy);
    if(r > d) r = d;
    dx = l1.x2 - l2.x2;
    dy = l1.y2 - l2.y2;
    d = sqrt(dx * dx + dy * dy);
    if(r > d) r = d;

    // l1 <-> l2.1
    double tmp;
    if(canPerpen(l1, l2.x1, l2.y1, tmp)) {
        if(r > tmp) r = tmp;
    }
    // l1 <-> l2.2
    if(canPerpen(l1, l2.x2, l2.y2, tmp)) {
        if(r > tmp) r = tmp;
    }
    // l2 <-> l1.1
    if(canPerpen(l2, l1.x1, l1.y1, tmp)) {
        if(r > tmp) r = tmp;
    }
    // l2 <-> l1.1
    if(canPerpen(l2, l1.x2, l1.y2, tmp)) {
        if(r > tmp) r = tmp;
    }

    return r;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> al[i].x1 >> al[i].y1 >> al[i].x2 >> al[i].y2;
    }
    for(int i = 0; i < m; i++) {
        cin >> bl[i].x1 >> bl[i].y1 >> bl[i].x2 >> bl[i].y2;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            double d = dis(al[i], bl[j]);
            if(res > d) res = d;
        }
    }

    cout << fixed << setprecision(10);
    cout << res;

    return 0;
}
