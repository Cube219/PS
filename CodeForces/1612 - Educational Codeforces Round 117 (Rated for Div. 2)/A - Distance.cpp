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
int x, y;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> x >> y;
        int dis = x + y;

        int r1 = -1, r2 = -1;
        for(int i = 0; i <= 100; ++i) {
            for(int j = 0; j <= 100; ++j) {
                int d1 = i + j;
                int d2 = abs(i - x) + abs(j - y);
                if(d1 == dis / 2 && d2 == dis / 2) {
                    r1 = i;
                    r2 = j;
                    break;
                }
            }
            if(r1 != -1) break;
        }
        cout << r1 << " " << r2 << "\n";
    }

    return 0;
}
