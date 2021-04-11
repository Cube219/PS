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
int n, k, k2;
int d[101];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        k2 = k;
        for(int i = 0; i < n; ++i) {
            d[i] = 0;
        }

        int cur = n;
        for(int i = 1; i < n; i += 2) {
            if(k <= 0) break;
            d[i] = cur;
            cur--;
            k--;
        }
        if(k > 0 || (n <= k2 * 2)) {
            cout << "-1\n";
            continue;
        }

        for(int i = 0; i < n; ++i) {
            if(d[i] == 0) {
                d[i] = cur;
                cur--;
            }
        }
        for(int i = 0; i < n; ++i) {
            cout << d[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
