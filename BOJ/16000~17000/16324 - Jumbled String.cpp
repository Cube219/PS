#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

int a, b, c, d;
int zeronum, onenum;

int getnum(ll a)
{
    if(a == 0) return 0;
    for(ll i = 2; i < 50000; ++i) {
        ll v = i * (i - 1) / 2;
        if(v == a) return i;
        else if(v > a) return -1;
    }
    return 0;
}

void special()
{
    if(zeronum == 0 && onenum == 0) {
        if(b == 1 && c == 0) {
            cout << "01";
        } else if(b == 0 && c == 1) {
            cout << "10";
        } else if(b == 0 && c == 0) {
            cout << "0";
        } else {
            cout << "impossible";
        }
        return;
    }
    if(b == 0 && c == 0) {
        if(zeronum > 0) {
            for(int i = 0; i < zeronum; ++i) {
                cout << "0";
            }
        } else {
            for(int i = 0; i < onenum; ++i) {
                cout << "1";
            }
        }
        return;
    }
    if(b + c == max(zeronum, onenum)) {
        if(zeronum > 0) {
            for(int i = 0; i < b; ++i) {
                cout << "0";
            }
            cout << "1";
            for(int i = 0; i < c; ++i) {
                cout << "0";
            }
        } else {
            for(int i = 0; i < c; ++i) {
                cout << "1";
            }
            cout << "0";
            for(int i = 0; i < b; ++i) {
                cout << "1";
            }
        }
        return;
    }
    cout << "impossible";
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b >> c >> d;
    zeronum = getnum(a);
    onenum = getnum(d);
    if(zeronum == -1 || onenum == -1) {
        cout << "impossible";
        return 0;
    }
    if(zeronum == 0 || onenum == 0) {
        special();
        return 0;
    }
    if(b + c != zeronum * onenum) {
        cout << "impossible";
        return 0;
    }
    int leftnum = c / zeronum;
    c = c % zeronum;
    for(int i = 0; i < leftnum; ++i) {
        cout << "1";
    }
    for(int i = 0; i < zeronum - c; ++i) {
        cout << "0";
    }
    if(onenum - leftnum > 0) {
        cout << "1";
    }
    for(int i = 0; i < c; ++i) {
        cout << "0";
    }
    for(int i = 0; i < onenum - leftnum - 1; ++i) {
        cout << "1";
    }

    return 0;
}
