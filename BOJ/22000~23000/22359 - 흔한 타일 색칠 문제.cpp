#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;

using ll = long long int;

int t, n, n2;
int x, y;
vector<vector<char>> map[11];

char res[1025][1025];

void build()
{
    for(int i = 1; i <= n; ++i) {
        int i2 = 1 << i;
        map[i].resize(i2);
        for(int k = 0; k < i2; ++k) {
            map[i][k].resize(i2);
        }
    }

    map[1][0][0] = 'a';
    map[1][0][1] = 'a';
    map[1][1][0] = 'a';
    map[1][1][1] = 'c';

    for(int sz = 2; sz <= n; ++sz) {
        int sz2 = (1 << sz);
        int sz22 = sz2 / 2;

        for(int i = 0; i < sz22; ++i) {
            for(int j = 0; j < sz22; ++j) {
                char ch = map[sz - 1][i][j];
                char ch2 = ch;
                if(ch2 == 'a') ch2 = 'b';
                else if(ch2 == 'b') ch2 = 'a';

                map[sz][i][j] = ch;
                map[sz][sz2 - i - 1][j] = ch2;
                map[sz][i][sz2 - j - 1] = ch2;
                map[sz][sz22 + i][sz22 + j] = ch;
            }
        }

        map[sz][sz22 - 1][sz22 - 1] = 'c';
        map[sz][sz22 - 1][sz22] = 'c';
        map[sz][sz22][sz22 - 1] = 'c';
    }
}

void p(int sz, int px, int py, int offsetx, int offsety)
{
    if(sz == 1) {
        char ch = '!';
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                char cc = res[offsetx + i][offsety + j];
                if(cc == 'a' || cc == 'b') {
                    ch = cc;
                    break;
                }
            }
            if(ch != '!') break;
        }
        if(ch == '!') ch = 'a';

        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                res[offsetx + i][offsety + j] = ch;
            }
        }
        res[offsetx + px][offsety + py] = '@';
        return;
    }

    int sz2 = (1 << sz);

    int sz22 = sz2 / 2;
    if(px < sz22 && py < sz22) {
        for(int i = 0; i < sz2; ++i) {
            for(int j = 0; j < sz2; ++j) {
                char ch = map[sz][sz2 - i - 1][sz2 - j - 1];
                res[offsetx + i][offsety + j] = ch;
            }
        }
        p(sz - 1, px, py, offsetx, offsety);
    } else if(px < sz22 && py >= sz22) {
        for(int i = 0; i < sz2; ++i) {
            for(int j = 0; j < sz2; ++j) {
                char ch = map[sz][sz2 - i - 1][j];
                if(ch == 'a') ch = 'b';
                else if(ch == 'b') ch = 'a';
                res[offsetx + i][offsety + j] = ch;
            }
        }
        p(sz - 1, px, py - sz22, offsetx, offsety + sz22);
    } else if(px >= sz22 && py < sz22) {
        for(int i = 0; i < sz2; ++i) {
            for(int j = 0; j < sz2; ++j) {
                char ch = map[sz][i][sz2 - j - 1];
                if(ch == 'a') ch = 'b';
                else if(ch == 'b') ch = 'a';
                res[offsetx + i][offsety + j] = ch;
            }
        }
        p(sz - 1, px - sz22, py, offsetx + sz22, offsety);
    } else {
        for(int i = 0; i < sz2; ++i) {
            for(int j = 0; j < sz2; ++j) {
                char ch = map[sz][i][j];
                res[offsetx + i][offsety + j] = ch;
            }
        }
        p(sz - 1, px - sz22, py - sz22, offsetx + sz22, offsety + sz22);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> t >> n;
    n2 = (1 << n);
    build();

    for(int i = 0; i < t; ++i) {
        cin >> x >> y;
        x--; y--;

        p(n, x, y, 0, 0);

        for(int j = 0; j < n2; ++j) {
            for(int k = 0; k < n2; ++k) {
                cout << res[j][k];
            }
            cout << "\n";
        }
    }

    return 0;
}
