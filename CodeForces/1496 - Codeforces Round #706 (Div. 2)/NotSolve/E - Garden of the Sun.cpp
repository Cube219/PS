#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, m;
char map[502][502];
bool has[502];
int lastR;
int minR[502];
 
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
            has[i] = false;
            minR[i] = 987654321;
        }
        lastR = -1;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(map[i][j] == 'X') {
                    lastR = max(lastR, i);
                }
            }
        }
 
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < lastR; ++j) {
                if(map[j][i] == 'X') {
                    has[i] = true;
                    minR[i] = j;
                    break;
                }
            }
        }
 
        bool beforeHas = false;
        for(int i = 0; i < m; ++i) {
            if(beforeHas == true) {
                beforeHas = false;
                continue;
            }
 
            if(has[i] == true && beforeHas == false) {
                for(int j = 0; j <= lastR; ++j) {
                    map[j][i] = 'X';
                }
                beforeHas = true;
            }
        }
 
        for(int i = 0; i < m; ++i) {
            map[lastR][i] = 'X';
        }
 
        for(int i = 1; i < m - 1; ++i) {
            if(has[i - 1] == true && has[i] == true && has[i + 1] == true) {
                map[lastR][i] = '.';
                has[i] = false;
            }
        }
        for(int i = 0; i < n; ++i) {
            cout << map[i] << "\n";
        }
    }
 
    return 0;
}
