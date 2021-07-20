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
ll d[1000001];

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
    int res = 0;

    int l = 0, r = n - 1;
    ll curl = d[l], curr = d[r];
    while(l < r) {
        if(curl == curr) {
            l++;
            r--;
            curl = d[l];
            curr = d[r];
        } else if(curl < curr) {
            l++;
            curl += d[l];
            res++;
        } else {
            r--;
            curr += d[r];
            res++;
        }
    }

    cout << res;

    return 0;
}
