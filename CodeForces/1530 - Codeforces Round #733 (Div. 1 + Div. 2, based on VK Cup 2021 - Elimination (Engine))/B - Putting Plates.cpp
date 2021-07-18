#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int w, h;
int mp[101][101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> h >> w;

        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                mp[i][j] = 0;
            }
        }

        for(int i = 0; i < w; ++i) {
            if(i % 2 == 0) mp[0][i] = 1;
            else mp[0][i] = 0;
        }

        for(int i = 1; i < h - 1; ++i) {
            if(mp[i - 1][0] == 0 && mp[i - 1][1] == 0) mp[i][0] = 1;
            if(mp[i - 1][w-1] == 0 && mp[i - 1][w-2] == 0) mp[i][w-1] = 1;
        }


        for(int i = 0; i < w; i += 2) {
            bool pos = true;
            if(i > 0 && mp[h - 2][i - 1] == 1) pos = false;
            if(mp[h - 2][i] == 1) pos = false;
            if(i + 1 < w && mp[h - 2][i + 1] == 1) pos = false;
            if(pos == true) mp[h - 1][i] = 1;
        }

        for(int i = 0; i < h; ++i) {
            for(int j = 0; j < w; ++j) {
                cout << mp[i][j];
            }
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
