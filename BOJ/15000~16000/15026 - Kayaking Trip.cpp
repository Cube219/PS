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
int num[3], v[3];
int c[100001];

bool ck(int k)
{
    int cnum[3];
    for(int i = 0; i < 3; ++i) cnum[i] = num[i];

    for(int i = 0; i < n; ++i) {
        // bb
        if(cnum[0] > 1 && c[i] * (v[0] * 2) >= k) {
            cnum[0] -= 2;
            continue;
        }
        // bn
        if(cnum[0] > 0 && cnum[1] > 0 && c[i] * (v[0] + v[1]) >= k) {
            cnum[0]--;
            cnum[1]--;
            continue;
        }
        // be, nn
        if(v[0] + v[2] < v[1] + v[1]) {
            // be
            if(cnum[0] > 0 && cnum[2] > 0 && c[i] * (v[0] + v[2]) >= k) {
                cnum[0]--;
                cnum[2]--;
                continue;
            }
            // nn
            if(cnum[1] > 1 && c[i] * (v[1] * 2) >= k) {
                cnum[1] -= 2;
                continue;
            }
        } else {
            // nn
            if(cnum[1] > 1 && c[i] * (v[1] * 2) >= k) {
                cnum[1] -= 2;
                continue;
            }
            // be
            if(cnum[0] > 0 && cnum[2] > 0 && c[i] * (v[0] + v[2]) >= k) {
                cnum[0]--;
                cnum[2]--;
                continue;
            }
        }
        // ne
        if(cnum[1] > 0 && cnum[2] > 0 && c[i] * (v[1] + v[2]) >= k) {
            cnum[1]--;
            cnum[2]--;
            continue;
        }
        // ee
        if(cnum[2] > 1 && c[i] * (v[2] * 2) >= k) {
            cnum[2] -= 2;
            continue;
        }
        return false;
    }
    return true;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> num[0] >> num[1] >> num[2];
    n = num[0] + num[1] + num[2];
    n /= 2;
    for(int i = 0; i < 3; ++i) {
        cin >> v[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    sort(c, c + n);
    int l = 0, r = 200000001;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        if(ck(m) == true) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l;

    return 0;
}
