#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
ll res;
int map[100005][3];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n * 2; ++i) {
        int x, y;
        cin >> x >> y;

        int nx = x, ny = y;
        if(nx < 1) nx = 1;
        else if(nx > n) nx = n;
        if(ny > 2) ny = 2;
        else if(ny < 1) ny = 1;
        map[nx][ny]++;

        res += abs(x - nx);
        res += abs(y - ny);
    }

    int remain[3] = { 0, 0, 0 };
    for(int i = 1; i <= n; ++i) {
        remain[1] += map[i][1] - 1;
        remain[2] += map[i][2] - 1;

        if(remain[1] < 0 && remain[2] > 0) {
            int gap = min(-remain[1], remain[2]);
            remain[1] += gap;
            remain[2] -= gap;
            res += gap;
        }
        if(remain[1] > 0 && remain[2] < 0) {
            int gap = min(remain[1], -remain[2]);
            remain[1] -= gap;
            remain[2] += gap;
            res += gap;
        }

        res += abs(remain[1]);
        res += abs(remain[2]);
    }

    cout << res;

    return 0;
}
