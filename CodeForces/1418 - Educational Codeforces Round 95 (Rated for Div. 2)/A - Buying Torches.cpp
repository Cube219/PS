#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int x, y, k;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> x >> y >> k;
        x--;

        lli t1 = (lli)k * y;
        t1--;

        lli res = 0;
        res += (t1 - 1) / x;
        lli remain = (x * res + 1) - t1;

        if(remain < k) {
            res += (k - remain) / x;
        }

        cout << res + k + 1<< endl;
    }

    return 0;
}
