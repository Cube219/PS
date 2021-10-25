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
int n, q, a[2007];
int a2[2007][2007];
int cnt[2007];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 1; i <= n; ++i) {
            cin >> a[i];
            a2[0][i] = a[i];
        }

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                cnt[j] = 0;
            }

            for(int j = 1; j <= n; ++j) {
                cnt[a2[i - 1][j]]++;
            }
            for(int j = 1; j <= n; ++j) {
                a2[i][j] = cnt[a2[i - 1][j]];
            }
        }

        cin >> q;
        for(int i = 0; i < q; ++i) {
            int idx, step;
            cin >> idx >> step;
            if(step > n) step = n;
            cout << a2[step][idx] << "\n";
        }
    }

    return 0;
}
