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
int a, b, c;
ll aa, bb, cc;

int cnt(ll v)
{
    int res = 0;
    while(v > 0) {
        res++;
        v /= 10;
    }
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> a >> b >> c;
        cc = 1;
        while(cnt(cc) < c) {
            cc *= 7;
        }
        aa = cc;
        bb = cc;
        while(cnt(aa) < a) {
            aa *= 2;
        }
        while(cnt(bb) < b) {
            bb *= 5;
        }
        cout << aa << " " << bb << "\n";
    }

    return 0;
}
