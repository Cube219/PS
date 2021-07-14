#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int n, d[501][501];
int res[501][501];
int p[501][501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < n; ++j) {
            d[i][j] = str[j] - '0';
        }
    }
    for(int i = n - 2; i >= 0; --i) {
        for(int j = i + 1; j < n; ++j) {
            if(p[i][j] != d[i][j]) {
                res[i][j] = 1;
                p[i][j]++;
                p[i][j] %= 10;
                for(int k = j; k < n; ++k) {
                    p[i][k] += p[j][k];
                    p[i][k] %= 10;
                }
            }
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << res[i][j];
        }
        cout << "\n";
    }

    return 0;
}
