#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 9223372036854775800;

int tNum;
ll d[3][2];
ll res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {

        for(int i = 0; i < 3; ++i) {
            cin >> d[i][0] >> d[i][1];
        }

        res = INF;

        // ABC
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                for(int k = 0; k < 2; ++k) {
                    ll h = d[0][1 - i];
                    h = max(h, d[1][1 - j]);
                    h = max(h, d[2][1 - k]);
                    ll w = d[0][i] + d[1][j] + d[2][k];
                    res = min(res, w * h);
                }
            }
        }
        // 0
        // 12
        int per[] = { 0, 1, 2 };
        for(int z = 0; z < 6; ++z) {
            for(int i = 0; i < 2; ++i) {
                for(int j = 0; j < 2; ++j) {
                    for(int k = 0; k < 2; ++k) {
                        ll w = d[per[0]][i];
                        w = max(w, d[per[1]][j] + d[per[2]][k]);
                        ll h = d[per[0]][1 - i];
                        h += max(d[per[1]][1 - j], d[per[2]][1 - k]);
                        res = min(res, w * h);
                    }
                }
            }
            next_permutation(per, per + 3);
        }
        
        cout << res << "\n";
    }

    return 0;
}
