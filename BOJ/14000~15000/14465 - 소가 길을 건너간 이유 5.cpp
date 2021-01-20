#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n, k, b;
int d[100002];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> b;
    for(int i = 0; i < b; i++) {
        int bk;
        cin >> bk;
        d[bk] = 1;
    }

    int res = 0;
    int cnt = 0;
    for(int i = 1; i <= k; i++) {
        cnt += d[i];
    }
    res = cnt;
    for(int i = k + 1; i <= n; i++) {
        cnt -= d[i - k];
        cnt += d[i];
        if(res > cnt) res = cnt;
    }
    cout << res;

    return 0;
}
