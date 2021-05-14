#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int l, r;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> l >> r;
    if(l == r) {
        if(l == 0) cout << "Not a moose";
        else cout << "Even " << l * 2;
    } else {
        cout << "Odd " << max(l, r) * 2;
    }

    return 0;
}
