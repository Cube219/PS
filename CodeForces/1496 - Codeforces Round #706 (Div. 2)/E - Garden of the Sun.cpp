#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
char map[503][503];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            cin >> map[i];
        }

        for(int i = 0; i < m; ++i) {
            if(i % 3 != 0) continue;
            for(int j = 0; j < n; ++j) {
                map[j][i] = 'X';
            }
        }

        for(int i = 0; i < m; ++i) {
            if(i % 3 == 0) continue;
            if(i + 1 >= m) break;

            int idx = - 1;
            for(int j = 0; j < n; ++j) {
                if(map[j][i] == 'X') {
                    idx = j;
                    break;
                }
            }
            if(idx != -1) {
                map[idx][i + 1] = 'X';
                i++;
                continue;
            }

            for(int j = 0; j < n; ++j) {
                if(map[j][i + 1] == 'X') {
                    idx = j;
                    break;
                }
            }
            if(idx != -1) {
                map[idx][i] = 'X';
                i++;
                continue;
            }
            map[0][i] = 'X';
            map[0][i + 1] = 'X';
            i++;
        }

        if(m % 3 == 0) {
            for(int i = 0; i < n; ++i) {
                if(map[i][m - 1] != 'X') continue;

                for(int j = m - 2; j >= 0; --j) {
                    if(map[i][j] == 'X') break;
                    map[i][j] = 'X';
                }
            }
        }

        for(int i = 0; i < n; ++i) {
            cout << map[i] << "\n";
        }
    }

    return 0;
}
