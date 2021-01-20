#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int ccw(int x1, int y1, int x2, int y2)
{
    return x1 * y2 - x2 * y1;
}

int x1, y11, x2, y2, x3, y3;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> x1 >> y11;
    cin >> x2 >> y2;
    cin >> x3 >> y3;

    int res = ccw(x2 - x1, y2 - y11, x3 - x2, y3 - y2);

    if(res > 0) {
        cout << "1";
    } else if(res == 0) {
        cout << "0";
    } else {
        cout << "-1";
    }

    return 0;
}
