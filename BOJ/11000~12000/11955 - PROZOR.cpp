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

int n, m, sz;
char map[105][105];
int sum[105][105];
int res;
int rx, ry;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> sz;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == '*') {
                sum[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(i > 0) sum[i][j] += sum[i - 1][j];
            if(j > 0) sum[i][j] += sum[i][j - 1];
            if(i > 0 && j > 0) sum[i][j] -= sum[i - 1][j - 1];
        }
    }

    for(int i = sz - 1; i < n; ++i) {
        for(int j = sz - 1; j < m; ++j) {
            int cur = sum[i - 1][j - 1]
                - sum[i - sz + 1][j - 1] - sum[i - 1][j - sz + 1]
                + sum[i - sz + 1][j - sz + 1];
            if(res < cur) {
                res = cur;
                rx = i;
                ry = j;
            }
        }
    }
    map[rx][ry] = '+';
    map[rx - sz + 1][ry] = '+';
    map[rx][ry - sz + 1] = '+';
    map[rx - sz + 1][ry - sz + 1] = '+';
    for(int i = 1; i < sz - 1; ++i) {
        map[rx - i][ry] = '|';
        map[rx - i][ry - sz + 1] = '|';
        map[rx][ry - i] = '-';
        map[rx - sz + 1][ry - i] = '-';
    }
    cout << res << "\n";
    for(int i = 0; i < n; ++i) {
        cout << map[i] << "\n";
    }

    return 0;
}
