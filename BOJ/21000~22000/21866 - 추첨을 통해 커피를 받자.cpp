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
int d[] = { 100, 100, 200, 200, 300, 300, 400, 400, 500 };

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int sum = 0;
    bool h = false;
    for(int i = 0; i < 9; ++i) {
        int a;
        cin >> a;
        if(d[i] < a) {
            h = true;
        }
        sum += a;
    }
    if(h == true) cout << "hacker";
    else if(sum >= 100) cout << "draw";
    else cout << "none";

    return 0;
}
