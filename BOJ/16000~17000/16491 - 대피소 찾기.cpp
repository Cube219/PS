#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int ccw(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - x2 * y1;
}
int n;
int rx[11], ry[11];
int sx[11], sy[11];
int res[11];
bool isFinished;
bool isTaken[11];

struct Line
{
    int x1;
    int y1;
    int x2;
    int y2;
};
bool isCross(Line l1, Line l2)
{
    int vx = l1.x2 - l1.x1;
    int vy = l1.y2 - l1.y1;

    int ax = l2.x1 - l1.x2;
    int ay = l2.y1 - l1.y2;
    int bx = l2.x2 - l1.x2;
    int by = l2.y2 - l1.y2;

    int ccwa = ccw(vx, vy, ax, ay);
    int ccwb = ccw(vx, vy, bx, by);
    if((ccwa > 0 && ccwb > 0) || (ccwa < 0 && ccwb < 0)) return false;
    if(ccwa == 0 && ccwb == 0) {
        if(l1.x1 > l1.x2) swap(l1.x1, l1.x2);
        if(l1.y1 > l1.y2) swap(l1.y1, l1.y2);
        if(l2.x1 > l2.x2) swap(l2.x1, l2.x2);
        if(l2.y1 > l2.y2) swap(l2.y1, l2.y2);

        if(l1.x2 < l2.x1) return false;
        if(l2.x2 < l1.x1) return false;
        if(l1.y2 < l2.y1) return false;
        if(l2.y2 < l1.y1) return false;

        return true;
    }

    vx = l2.x2 - l2.x1;
    vy = l2.y2 - l2.y1;

    ax = l1.x1 - l2.x2;
    ay = l1.y1 - l2.y2;
    bx = l1.x2 - l2.x2;
    by = l1.y2 - l2.y2;

    ccwa = ccw(vx, vy, ax, ay);
    ccwb = ccw(vx, vy, bx, by);
    if((ccwa > 0 && ccwb > 0) || (ccwa < 0 && ccwb < 0)) return false;

    return true;
}

bool isValid()
{
    Line l1, l2;

    for(int i = 0; i < n - 1; i++) {
        int iRes = res[i];
        l1 = { rx[i], ry[i], sx[iRes], sy[iRes] };
        for(int j = i + 1; j < n; j++) {
            int jRes = res[j];
            l2 = { rx[j], ry[j], sx[jRes], sy[jRes] };
            if(isCross(l1, l2) == true) return false;
        }
    }
    return true;
}

void p(int x)
{
    if(x == n) {
        if(isValid() == true) {
            isFinished = true;
        }
        return;
    }

    for(int i = 0; i < n; i++) {
        if(isTaken[i] == true) continue;

        isTaken[i] = true;
        res[x] = i;
        p(x + 1);

        isTaken[i] = false;
        
        if(isFinished == true) return;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> rx[i] >> ry[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> sx[i] >> sy[i];
    }

    p(0);

    for(int i = 0; i < n; i++) {
        cout << res[i] + 1 << "\n";
    }

    return 0;
}
