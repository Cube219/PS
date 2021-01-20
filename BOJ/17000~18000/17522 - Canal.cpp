#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string.h>
#include <iomanip>
using namespace std;

using lli = long long int;

int n;

struct Dot
{
    int x;
    int y;
};
Dot dx[300001];
lli minLeft[300001], minRight[300001], maxLeft[300001], maxRight[300001];

bool ck(lli distance)
{
    bool isPossible = false;
    int l = 0, r = 0;
    while(1) {
        for(; r < n; r++) {
            if((lli)dx[r].x - dx[l].x > distance) break;
        }
        r--;

        lli yMin = 4000000001, yMax = -4000000001;
        if(l > 0) {
            if(yMin > minLeft[l - 1]) yMin = minLeft[l - 1];
            if(yMax < maxLeft[l - 1]) yMax = maxLeft[l - 1];
        }
        if(r < n - 1) {
            if(yMin > minRight[r + 1]) yMin = minRight[r + 1];
            if(yMax < maxRight[r + 1]) yMax = maxRight[r + 1];
        }
        if(yMax - yMin <= distance) {
            isPossible = true;
            break;
        }

        if(r == n - 1) {
            break;
        }
        l++;
    }

    return isPossible;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x *= 2;
        y *= 2;
        dx[i] = { x, y };
    }

    sort(dx, dx + n, [](const Dot& l, const Dot& r) {
        return l.x < r.x;
    });
    minLeft[0] = dx[0].y;
    maxLeft[0] = dx[0].y;
    for(int i = 1; i < n; i++) {
        minLeft[i] = minLeft[i - 1];
        maxLeft[i] = maxLeft[i - 1];

        if(minLeft[i] > dx[i].y) minLeft[i] = dx[i].y;
        if(maxLeft[i] < dx[i].y) maxLeft[i] = dx[i].y;
    }
    minRight[n - 1] = dx[n - 1].y;
    maxRight[n - 1] = dx[n - 1].y;
    for(int i = n - 2; i >= 0; i--) {
        minRight[i] = minRight[i + 1];
        maxRight[i] = maxRight[i + 1];

        if(minRight[i] > dx[i].y) minRight[i] = dx[i].y;
        if(maxRight[i] < dx[i].y) maxRight[i] = dx[i].y;
    }

    lli l = 0, h = 4000000000;
    lli res = 4000000001;
    while(l <= h) {
        // cout << l << " " << h << endl;
        lli m = (l + h) / 2;

        if(ck(m) == true) {
            if(res > m) res = m;

            h = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << fixed << setprecision(1) << res / 4.0;

    return 0;
}
