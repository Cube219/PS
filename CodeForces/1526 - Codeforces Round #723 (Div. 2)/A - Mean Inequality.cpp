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
int n;
int d[51];
int res[51];

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
        n *= 2;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n);
        for(int j = 0; j < n; ++j) {
            if(j % 2 == 0) res[j] = d[j / 2];
            else res[j] = d[j / 2 + n / 2];
        }

        for(int i = 0; i < n; ++i) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
