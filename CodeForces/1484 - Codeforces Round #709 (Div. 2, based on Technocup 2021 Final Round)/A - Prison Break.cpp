#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int a, b;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> a >> b;
        int t = (a + 1) * (b + 1);
        t--;
        int t2 = (a + 1) * b;
        t2 += (b + 1) * a;
        cout << t2 - t << "\n";
    }

    return 0;
}
