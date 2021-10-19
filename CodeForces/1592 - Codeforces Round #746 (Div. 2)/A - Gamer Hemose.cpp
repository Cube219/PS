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
int h, n;
int d[10001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> h;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n);
        int sum = d[n - 1] + d[n - 2];
        int res = (h / sum) * 2;
        h %= sum;
        int f = 0;
        while(h > 0) {
            if(f == 0) h -= d[n - 1];
            else h -= d[n - 2];
            f = 1 - f;
            res++;
        }
        cout << res << "\n";
    }

    return 0;
}
