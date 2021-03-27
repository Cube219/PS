#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

using ll = long long int;

int n;
struct Point
{
    int x, y;
};
Point p1, p2;

constexpr double PI = 3.141592653589793238;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    // ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    double mx = (double)(p1.x + p2.x) / 2.0;
    double my = (double)(p1.y + p2.y) / 2.0;
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    double l = sqrt(dx * dx + dy * dy);
    l /= 2;

    double angle = atan2(p1.y - my, p1.x - mx);
    /*if((p1.x < p2.x && p1.y < p2.y) || (p1.x > p2.x && p1.y > p2.y)) {
        angle -= PI;
    }*/

    double pa = 2.0 * PI / n;
    angle += pa;

    double rx = cos(angle) * l + mx;
    double ry = sin(angle) * l + my;

    printf("%.11lf %.11lf", rx, ry);

    return 0;
}
