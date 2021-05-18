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
int res;
int d[501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    int cnt = 0;
    int idx = 0;
    int cur = 0;
    for(int i = 1; i <= 366; ++i) {
        if(cur + cnt >= 20) {
            res++;
            cnt = 0;
            cur = 0;
        }
        cur += cnt;
        if(i == d[idx]) {
            cnt++;
            //cur++;
            idx++;
        }
    }
    if(cur > 0) res++;

    cout << res;

    return 0;
}
