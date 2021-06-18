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
int d[200001];

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
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n);
        int gap = d[1] - d[0];
        int idx = 0;
        if(gap > d[n-1]-d[n-2]) {
            gap = d[n - 1] - d[n - 2];
            idx = n - 2;
        }
        for(int i = 0; i < n - 2; ++i) {
            if(gap > d[i+1]-d[i]) {
                gap = d[i + 1] - d[i];
                idx = i;
            }
        }
        if(n == 2) {
            for(int i = 0; i < n; ++i) {
                cout << d[i] << " ";
            }
            cout << "\n";
        } else {
            for(int i = idx + 1; i < n; ++i) {
                cout << d[i] << " ";
            }
            for(int i = 0; i <= idx; ++i) {
                cout << d[i] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
