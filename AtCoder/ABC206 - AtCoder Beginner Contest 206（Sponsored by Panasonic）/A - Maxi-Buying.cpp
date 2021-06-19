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

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    cin >> n;
    double d = (double)n * 1.08;
    int res = (int)d;
    if(res < 206) cout << "Yay!";
    else if(res == 206) cout << "so-so";
    else cout << ":(";

    return 0;
}
