#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int n, d[100001], num[4], d2[100001];
int p[4][4];
int res;

int calc()
{
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            p[i][j] = 0;
        }
    }

    for(int i = 0; i < n; i++) {
        if(d[i] == d2[i]) continue;

        p[d[i]][d2[i]]++;
    }

    int res = 0;

    // 1-2 2-1
    int tmp = min(p[1][2], p[2][1]);
    res += tmp;
    p[1][2] -= tmp;
    p[2][1] -= tmp;

    // 1-3 3-1
    tmp = min(p[1][3], p[3][1]);
    res += tmp;
    p[1][3] -= tmp;
    p[3][1] -= tmp;

    // 2-3 3-2
    tmp = min(p[2][3], p[3][2]);
    res += tmp;
    p[2][3] -= tmp;
    p[3][2] -= tmp;

    // remain
    if(p[1][2] != 0) {
        res += p[1][2] * 2;
    } else if(p[1][3] != 0) {
        res += p[1][3] * 2;
    }

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> d[i];
        num[d[i]]++;
    }

    res = 987654321;

    // 1 2 3
    int idx = 0;
    for(int i = 0; i < num[1]; i++) {
        d2[idx++] = 1;
    }
    for(int i = 0; i < num[2]; i++) {
        d2[idx++] = 2;
    }
    for(int i = 0; i < num[3]; i++) {
        d2[idx++] = 3;
    }

    int r = calc();
    if(res > r) res = r;

    // 1 3 2
    idx = 0;
    for(int i = 0; i < num[1]; i++) {
        d2[idx++] = 1;
    }
    for(int i = 0; i < num[3]; i++) {
        d2[idx++] = 3;
    }
    for(int i = 0; i < num[2]; i++) {
        d2[idx++] = 2;
    }

    r = calc();
    if(res > r) res = r;

    // 2 1 3
    idx = 0;
    for(int i = 0; i < num[2]; i++) {
        d2[idx++] = 2;
    }
    for(int i = 0; i < num[1]; i++) {
        d2[idx++] = 1;
    }
    for(int i = 0; i < num[3]; i++) {
        d2[idx++] = 3;
    }

    r = calc();
    if(res > r) res = r;

    // 2 3 1
    idx = 0;
    for(int i = 0; i < num[2]; i++) {
        d2[idx++] = 2;
    }
    for(int i = 0; i < num[3]; i++) {
        d2[idx++] = 3;
    }
    for(int i = 0; i < num[1]; i++) {
        d2[idx++] = 1;
    }

    r = calc();
    if(res > r) res = r;

    // 3 1 2
    idx = 0;
    for(int i = 0; i < num[3]; i++) {
        d2[idx++] = 3;
    }
    for(int i = 0; i < num[1]; i++) {
        d2[idx++] = 1;
    }
    for(int i = 0; i < num[2]; i++) {
        d2[idx++] = 2;
    }

    r = calc();
    if(res > r) res = r;

    // 3 2 1
    idx = 0;
    for(int i = 0; i < num[3]; i++) {
        d2[idx++] = 3;
    }
    for(int i = 0; i < num[2]; i++) {
        d2[idx++] = 2;
    }
    for(int i = 0; i < num[1]; i++) {
        d2[idx++] = 1;
    }

    r = calc();
    if(res > r) res = r;

    cout << res;

    return 0;
}
