#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

using ll = long long int;

vector<int> g[505];
int a[505], b[505];
bool isComp[505];
bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == -1) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt]);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

int tNum;
char d[2006][2006], str[1006];
int h, v, sl, hInfo[2006][2006];
int maxX, maxY;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        maxX = 0; maxY = 0;
        cin >> h >> v;
        for(int i = 0; i < h; ++i) {
            int x, y;
            cin >> x >> y >> str;
            sl = strlen(str);
            for(int j = 0; j < sl; ++j) {
                d[y][x + j] = str[j];
                hInfo[y][x + j] = i + 1;
                maxX = max(maxX, x + j);
                maxY = max(maxY, y);
            }
        }
        for(int i = 0; i < v; ++i) {
            int x, y;
            cin >> x >> y >> str;
            sl = strlen(str);
            for(int j = 0; j < sl; ++j) {
                if(hInfo[y + j][x] != 0 && d[y + j][x] != str[j]) {
                    g[hInfo[y + j][x]].push_back(i + 1);
                }
                maxX = max(maxX, x);
                maxY = max(maxY, y + j);
            }
        }

        for(int i = 1; i <= h; ++i) {
            a[i] = -1;
        }
        for(int i = 1; i <= v; ++i) {
            b[i] = -1;
        }
        int res = 0;
        for(int i = 1; i <= h; ++i) {
            if(a[i] == -1) {
                for(int j = 1; j <=h; ++j) {
                    isComp[j] = false;
                }
                if(bp(i) == true) res++;
            }
        }

        cout << h + v - res << "\n";

        memset(d, 0, sizeof(d));
        memset(hInfo, 0, sizeof(hInfo));
        for(int i = 1; i <= h; ++i) {
            g[i].clear();
        }
    }

    return 0;
}
