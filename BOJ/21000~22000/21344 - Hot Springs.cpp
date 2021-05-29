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
int d[100001];
int res[100001];

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
    sort(d, d + n);
    int l = n / 2;
    int r = l;
    for(int i = 0; i < n; ++i) {
        if(i % 2 == 0) {
            res[i] = d[r];
            l--;
        } else {
            res[i] = d[l];
            r++;
        }
    }

    for(int i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
