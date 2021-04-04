#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // use y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int d[101][101];
int x1, y1, x2, y2;
bool oneComp, twoComp;

void debug()
{
    // cout << "##############\n";
    // for(int i = 1; i <= n; ++i)
    // {
    //     for(int j = 1; j <= n; ++j)
    //     {
    //         cout << d[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << "##############\n";
}

void fillOne()
{
    cout << "1 " << x1 << " " << y1 << endl;
    d[x1][y1] = 1;
    debug();
    y1 += 2;
    if(y1 > n) {
        x1++;
        if(x1 % 2 == 1) y1 = 1;
        else y1 = 2;
    }
    if(x1 > n) oneComp = true;
}

void fillTwo()
{
    cout << "2 " << x2 << " " << y2 << endl;
    d[x2][y2] = 2;
    debug();
    y2 += 2;
    if(y2 > n) {
        x2++;
        if(x2 % 2 == 0) y2 = 1;
        else y2 = 2;
    }
    if(x2 > n) twoComp = true;
}

void fillAny(int v)
{
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(d[i][j] == 0) {
                cout << v << " " << i << " " << j << endl;
                d[i][j] = v;
                debug();
                return;
            }
        }
    }
}

int main(void)
{
    x1 = 1;
    y1 = 1;
    x2 = 1;
    y2 = 2;
    cin >> n;
    for(int i = 0; i < n * n; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            if(oneComp == true || twoComp == true) {
                fillAny(3);
            } else {
                fillTwo();
            }
        } else if(a == 2) {
            if(oneComp == true || twoComp == true) {
                fillAny(3);
            } else {
                fillOne();
            }
        } else {
            if(oneComp == true) {
                fillAny(2);
            } else if(twoComp == true) {
                fillAny(1);
            } else {
                fillOne();
            }
        }
    }
    return 0;
}
