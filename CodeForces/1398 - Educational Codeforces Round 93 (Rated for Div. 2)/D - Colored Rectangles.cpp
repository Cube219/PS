#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <functional>
using namespace std;

using lli = long long int;

int rNum, gNum, bNum;
int r[202], g[202], b[202];
int d[202][202][202];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> rNum >> gNum >> bNum;
    for(int i = 1; i <= rNum; i++) cin >> r[i];
    for(int i = 1; i <= gNum; i++) cin >> g[i];
    for(int i = 1; i <= bNum; i++) cin >> b[i];

    sort(r + 1, r + rNum + 1, greater<int>());
    sort(g + 1, g + gNum + 1, greater<int>());
    sort(b + 1, b + bNum + 1, greater<int>());

    for(int i = 0; i <= rNum; i++) {
        for(int j = 0; j <= gNum; j++) {
            for(int k = 0; k <= bNum; k++) {
                int mx = 0;
                if(i > 0 && mx < d[i - 1][j][k]) mx = d[i - 1][j][k];
                if(j > 0 && mx < d[i][j - 1][k]) mx = d[i][j - 1][k];
                if(k > 0 && mx < d[i][j][k - 1]) mx = d[i][j][k - 1];
                if(i > 0 && j > 0 && mx < d[i - 1][j - 1][k] + r[i] * g[j]) mx = d[i - 1][j - 1][k] + r[i] * g[j];
                if(i > 0 && k > 0 && mx < d[i - 1][j][k - 1] + r[i] * b[k]) mx = d[i - 1][j][k - 1] + r[i] * b[k];
                if(j > 0 && k > 0 && mx < d[i][j - 1][k - 1] + g[j] * b[k]) mx = d[i][j - 1][k - 1] + g[j] * b[k];
                d[i][j][k] = mx;
            }
        }
    }

    cout << d[rNum][gNum][bNum];

    return 0;
}
