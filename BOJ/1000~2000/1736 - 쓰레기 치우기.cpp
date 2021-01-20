#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using lli = long long int;
int n, m, a[101][101];
int res, remain;

int getTop(int j)
{
    int res = 999;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i][j] == 1) res = i;
    }

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 1) remain++;
        }
    }

    while(remain > 0) {
        res++;
        int i = n - 1;
        for(int j = m - 1; j >= 0; j--) {
            int topI = getTop(j);
            while(i > topI) {
                if(a[i][j] == 1) remain--;
                a[i][j] = 0;
                i--;
            }
            if(a[i][j] == 1) remain--;
            a[i][j] = 0;
        }
    }

    cout << res;

    return 0;
}
