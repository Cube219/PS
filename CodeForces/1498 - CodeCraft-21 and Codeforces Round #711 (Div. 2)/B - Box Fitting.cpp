#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, w;
int d[100001];
int remain[100002];
int rNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1, cnt = 0;

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> w;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n);
        for(int i = 0; i <= n; ++i) {
            remain[i] = w;
        }

        for(int i = n - 1; i >= 0; --i) {
            int idx = lower_bound(remain, remain + n, d[i]) - remain;
            if(idx > rNum - 1) {
                rNum = idx + 1;
            }
            remain[idx] -= d[i];
        }
        cout << rNum << "\n";
    }

    return 0;
}
