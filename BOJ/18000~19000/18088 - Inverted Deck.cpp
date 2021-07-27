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
int d[1000001];
int d2[1000001];
bool diff[1000001];

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
        d2[i] = d[i];
    }

    sort(d2, d2 + n);

    for(int i = 0; i < n; ++i) {
        if(d[i] != d2[i]) diff[i] = true;
    }

    int r1 = -1, r2 = 0;

    int l = n - 1, r = 0;
    for(int i = 0; i < n; ++i) {
        if(diff[i] == true) {
            l = i;
            r1 = i;
            break;
        }
    }
    for(int i = n - 1; i >= 0; --i) {
        if(diff[i] == true) {
            r = i;
            r2 = i;
            break;
        }
    }
    if(l == n - 1) {
        r1 = 0;
        r2 = 0;
    }
    while(l <= r) {
        if(d2[l] != d[r] || d2[r] != d[l]) {
            r1 = -1;
            break;
        }
        l++;
        r--;
    }

    if(r1 == -1) {
        cout << "impossible";
    } else {
        cout << r1 + 1 << " " << r2 + 1;
    }

    return 0;
}
