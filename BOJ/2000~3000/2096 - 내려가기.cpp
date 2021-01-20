#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, mindp[2][3], maxdp[2][3];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        int idx = i % 2;
        for(int j = 0; j < 3; j++) {
            int a;
            cin >> a;
            mindp[idx][j] = a;
            maxdp[idx][j] = a;
        }

        if(i == 0) continue;

        int pIdx = 1 - idx;

        int maxV = max(maxdp[pIdx][0], maxdp[pIdx][1]);
        maxdp[idx][0] += maxV;
        maxV = max(maxV, maxdp[pIdx][2]);
        maxdp[idx][1] += maxV;
        maxV = max(maxdp[pIdx][1], maxdp[pIdx][2]);
        maxdp[idx][2] += maxV;

        int minV = min(mindp[pIdx][0], mindp[pIdx][1]);
        mindp[idx][0] += minV;
        minV = min(minV, mindp[pIdx][2]);
        mindp[idx][1] += minV;
        minV = min(mindp[pIdx][1], mindp[pIdx][2]);
        mindp[idx][2] += minV;
    }
    int idx = (n - 1) % 2;
    int maxRes = max(maxdp[idx][0], maxdp[idx][1]);
    maxRes = max(maxRes, maxdp[idx][2]);
    int minRes = min(mindp[idx][0], mindp[idx][1]);
    minRes = min(minRes, mindp[idx][2]);

    cout << maxRes << " " << minRes;

    return 0;
}
