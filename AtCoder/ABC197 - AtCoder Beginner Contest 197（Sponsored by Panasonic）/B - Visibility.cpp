#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int h, w, x, y;
char d[102][102];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> h >> w >> x >> y;
    x--;
    y--;
    for(int i = 0; i < h; ++i) {
        cin >> d[i];
    }

    int res = 1;
    int cx = x - 1;
    int cy = y;
    while(d[cx][cy] != '#' && cx >= 0) {
        res++;
        cx--;
    }
    cx = x + 1;
    cy = y;
    while(d[cx][cy] != '#' && cx < h) {
        res++;
        cx++;
    }
    cx = x;
    cy = y - 1;
    while(d[cx][cy] != '#' && cy >= 0) {
        res++;
        cy--;
    }
    cx = x;
    cy = y + 1;
    while(d[cx][cy] != '#' && cy < w) {
        res++;
        cy++;
    }
    cout << res;



    return 0;
}
