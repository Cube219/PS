#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using lli = long long int;

int tNum;
int n, a[100001];
bool nonNeg;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }

        sort(a, a + n);
        if(a[n - 1] < 0) {
            lli res = 1;
            for(int i = 0; i < 5; i++) {
                res *= (lli)a[n - i - 1];
            }

            cout << res << "\n";
            continue;
        }

        int st = 0, ed = n - 1;
        int cnt = 0;
        lli res = 1;
        while(1) {
            if(cnt <= 3 && a[st] * a[st + 1] > a[ed - 1] * a[ed]) {
                res = res * (lli)(a[st] * a[st + 1]);
                st += 2;
                cnt += 2;
            } else {
                res *= (lli)a[ed];
                ed--;
                cnt++;
            }

            if(cnt >= 5) break;
        }

        cout << res << "\n";
    }

    return 0;
}
