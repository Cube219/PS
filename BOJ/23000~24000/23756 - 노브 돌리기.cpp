#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int cur;
    int cost;
};

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a;
    cin >> n >> a;
    int res = 0;
    for(int i = 0; i < n; ++i) {
        int na;
        cin >> na;
        res += min(abs(a - na), 360 - abs(a - na));
        a = na;
    }
    cout << res;

    return 0;
}
