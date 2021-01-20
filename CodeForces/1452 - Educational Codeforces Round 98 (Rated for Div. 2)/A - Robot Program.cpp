#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int x, y;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> x >> y;
        if(x > y) swap(x, y);
        int res = x * 2;
        y -= x;
        if(y > 0) {
            res += y * 2 - 1;
        }
        cout << res << "\n";
    }

    return 0;
}
