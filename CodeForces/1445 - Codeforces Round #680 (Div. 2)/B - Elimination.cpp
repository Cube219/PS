#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int a, b, c, d;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> a >> b >> c >> d;

        int asum = a + b;
        int bsum = c + d;
        if(asum < bsum) res = bsum;
        else res = asum;

        cout << res << "\n";
    }

    return 0;
}
