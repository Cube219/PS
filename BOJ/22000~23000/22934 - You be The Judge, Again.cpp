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
int map[2001][2001];
int has[400001];
int znum;
int rmnum;

void p(int l, int r)
{
    int a = map[l][r];
    int b = map[l][r + 1];
    int c = map[l + 1][r];
    if(a != 0 && a == b && b == c) {
        has[a]++;
        map[l][r] = 0;
        map[l][r + 1] = 0;
        map[l + 1][r] = 0;
        rmnum += 3;
        return;
    }

    a = map[l][r];
    b = map[l + 1][r];
    c = map[l + 1][r + 1];
    if(a != 0 && a == b && b == c) {
        has[a]++;
        map[l][r] = 0;
        map[l + 1][r] = 0;
        map[l + 1][r + 1] = 0;
        rmnum += 3;
        return;
    }

    a = map[l][r + 1];
    b = map[l + 1][r];
    c = map[l + 1][r + 1];
    if(a != 0 && a == b && b == c) {
        has[a]++;
        map[l][r + 1] = 0;
        map[l + 1][r] = 0;
        map[l + 1][r + 1] = 0;
        rmnum += 3;
        return;
    }

    a = map[l][r];
    b = map[l][r + 1];
    c = map[l + 1][r + 1];
    if(a != 0 && a == b && b == c) {
        has[a]++;
        map[l][r] = 0;
        map[l][r + 1] = 0;
        map[l + 1][r + 1] = 0;
        rmnum += 3;
        return;
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int nn = 1 << n;
    for(int i = 0; i < nn; ++i) {
        for(int j = 0; j < nn; ++j) {
            cin >> map[i][j];
            if(map[i][j] == 0) znum++;
        }
    }

    for(int i = 0; i < nn - 1; ++i) {
        for(int j = 0; j < nn - 1; ++j) {
            p(i, j);
        }
    }

    if(znum != 1 || rmnum != nn*nn-1) {
        cout << "0";
        return 0;
    }

    int cnum = 1;
    for(int i = 0; i < n; ++i) {
        cnum *= 4;
    }
    cnum--;
    cnum /= 3;
    for(int i = 1; i <= cnum; ++i) {
        if(has[i] != 1) {
            cout << "0";
            return 0;
        }
    }

    cout << "1";

    return 0;
}
