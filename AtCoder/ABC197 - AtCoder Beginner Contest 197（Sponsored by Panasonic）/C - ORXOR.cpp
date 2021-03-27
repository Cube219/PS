#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
int d[22];
int res = 2147483647;
int t[30];

void p(int remain, int cnt, int cur, int mx)
{
    if(remain == 1) {
        t[cnt] = 0;
        for(int i = cur; i < n; ++i) {
            t[cnt] |= d[i];
        }
        int r = t[0];
        for(int i = 1; i <= cnt; ++i) {
            r = r ^ t[i];
        }
        res = min(res, r);
        return;
    }
    t[cnt] = 0;
    for(int i = cur; i <= n - remain; ++i) {
        t[cnt] |= d[i];
        p(remain - 1, cnt + 1, i + 1, mx);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    for(int i = 1; i <= n; ++i) {
        p(i, 0, 0, i);
    }
    cout << res;

    return 0;
}
