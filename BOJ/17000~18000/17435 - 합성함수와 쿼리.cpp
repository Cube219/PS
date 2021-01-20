#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int m, q, n, x;
int f[200001][30];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m;
    for(int i = 1; i <= m; i++) {
        cin >> f[i][0];
    }

    for(int i = 1; i < 30; i++) {
        for(int j = 1; j <= m; j++) {
            int v = j;
            v = f[v][i - 1];
            v = f[v][i - 1];
            f[j][i] = v;
        }
    }

    cin >> q;
    for(int i = 0; i < q; i++) {
        cin >> n >> x;
        for(int j = 0; j < 30; j++) {
            if(n % 2 == 1) {
                x = f[x][j];
            }
            n /= 2;
            if(n <= 0) break;
        }
        cout << x << "\n";
    }

    return 0;
}
