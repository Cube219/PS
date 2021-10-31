#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int t, n;
ll d[200001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> t;
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int l, r;
            cin >> l >> r;
            d[l]++;
            d[r]--;
        }
    }
    for(int i = 1; i <= 100000; ++i) {
        d[i] += d[i - 1];
    }
    ll res = 0, rl = 0, rr = t;
    ll cur = 0;
    for(int i = 0; i < t; ++i) {
        cur += d[i];
    }
    res = cur;
    for(int i = t; i <= 100000; ++i) {
        cur += d[i];
        cur -= d[i - t];
        if(res < cur) {
            res = cur;
            rl = i - t + 1;
            rr = i + 1;
        }
    }

    cout << rl << " " << rr;

    return 0;
}
