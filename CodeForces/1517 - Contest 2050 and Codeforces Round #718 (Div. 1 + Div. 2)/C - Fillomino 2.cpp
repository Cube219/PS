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
int map[505][505];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        map[i][i] = a;
    }

    for(int i = 0; i < n; ++i) {
        int cnt = map[i][i] - 1;
        int v = map[i][i];
        int x = i, y = i;
        while(cnt > 0) {
            if(y > 0 && map[x][y - 1] == 0) y--;
            else x++;
            map[x][y] = v;
            cnt--;
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= i; ++j) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
