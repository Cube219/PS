#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

using lli = long long int;

lli n;
lli d[26][26];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) {
        d[0][i] = 1;
        d[i][n - 1] = 1;
        d[i][n - 2] = i + 1;
    }

    lli maxV;
    for(int k = n - 3; k >= 0; k--) {
        maxV = 0;
        for(int i = 0; i < n; i++) {
            maxV += d[i][k + 1];
        }
        maxV += n - 1;

        lli re = 0;
        for(int i = k; i < n; i++) {
            maxV -= d[1][i];
        }
        maxV -= n - 2;
        maxV -= k + 1;
        maxV++;

        for(int i = 1; i < n; i++) {
            d[i][k] = maxV;
            maxV++;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << d[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
