#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

using ll = long long int;

int tNum;
ll xMin, yMin, xMax, yMax;
ll x1, yy1, x2, y2;
int pNum;
int ppNum;
bool isInf;

struct Line
{
    ll x1;
    ll y1;
    ll x2;
    ll y2;
};

ll ccw(ll x1, ll y1, ll x2, ll y2)
{
    return x1 * y2 - x2 * y1;
}

ll intersect(Line l1, Line l2)
{
    ll lineDx = l1.x2 - l1.x1;
    ll lineDy = l1.y2 - l1.y1;
    ll pointDx = l2.x1 - l1.x2;
    ll pointDy = l2.y1 - l1.y2;
    ll c1 = ccw(lineDx, lineDy, pointDx, pointDy);
    pointDx = l2.x2 - l1.x2;
    pointDy = l2.y2 - l1.y2;
    ll c2 = ccw(lineDx, lineDy, pointDx, pointDy);
    if((c1 > 0 && c2 > 0) || (c1 < 0 && c2 < 0)) return -1;

    lineDx = l2.x2 - l2.x1;
    lineDy = l2.y2 - l2.y1;
    pointDx = l1.x1 - l2.x2;
    pointDy = l1.y1 - l2.y2;
    c1 = ccw(lineDx, lineDy, pointDx, pointDy);
    pointDx = l1.x2 - l2.x2;
    pointDy = l1.y2 - l2.y2;
    c2 = ccw(lineDx, lineDy, pointDx, pointDy);

    if((c1 > 0 && c2 > 0) || (c1 < 0 && c2 < 0)) return -1;
    else if(c1 == 0 || c2 == 0) return 0;
    else return 1;
}

bool isInfX(Line sqLine, Line line)
{
    if(line.y1 != line.y2) return false;

    ll lineX1 = line.x1;
    ll lineX2 = line.x2;
    if(lineX1 > lineX2) swap(lineX1, lineX2);

    if(sqLine.x1 < lineX1 && lineX1 < sqLine.x2) return true;
    if(sqLine.x1 < lineX2 && lineX2 < sqLine.x2) return true;
    if(lineX1 < sqLine.x1 && sqLine.x1 < lineX2) return true;
    if(lineX1 < sqLine.x2 && sqLine.x2 < lineX2) return true;
    if(sqLine.x1 == lineX1 && sqLine.x2 == lineX2) return true;
    return false;
}

bool isInfY(Line sqLine, Line line)
{
    if(line.x1 != line.x2) return false;

    ll lineY1 = line.y1;
    ll lineY2 = line.y2;
    if(lineY1 > lineY2) swap(lineY1, lineY2);

    if(sqLine.y1 < lineY1 && lineY1 < sqLine.y2) return true;
    if(sqLine.y1 < lineY2 && lineY2 < sqLine.y2) return true;
    if(lineY1 < sqLine.y1 && sqLine.y1 < lineY2) return true;
    if(lineY1 < sqLine.y2 && sqLine.y2 < lineY2) return true;
    if(sqLine.y1 == lineY1 && sqLine.y2 == lineY2) return true;
    return false;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        pNum = 0;
        ppNum = 0;
        isInf = false;

        cin >> xMin >> yMin >> xMax >> yMax >> x1 >> yy1 >> x2 >> y2;

        Line line = { x1, yy1, x2, y2 };
        Line sqLine = { xMin, yMin, xMax, yMin };
        ll res = intersect(sqLine, line);
        if(res == 0) {
            if(isInfX(sqLine, line)) isInf = true;
            ppNum++;
        } else if(res == 1) pNum++;

        sqLine = { xMax, yMin, xMax, yMax };
        res = intersect(sqLine, line);
        if(res == 0) {
            if(isInfY(sqLine, line)) isInf = true;
            ppNum++;
        } else if(res == 1) pNum++;

        sqLine = { xMin, yMax, xMax, yMax };
        res = intersect(sqLine, line);
        if(res == 0) {
            if(isInfX(sqLine, line)) isInf = true;
            ppNum++;
        } else if(res == 1) pNum++;

        sqLine = { xMin, yMin, xMin, yMax };
        res = intersect(sqLine, line);
        if(res == 0) {
            if(isInfY(sqLine, line)) isInf = true;
            ppNum++;
        } else if(res == 1) pNum++;

        res = pNum + ppNum / 2;
        if(isInf == true) cout << "4\n";
        else cout << res << "\n";
    }

    return 0;
}
