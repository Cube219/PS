#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
lli n, a[100001];

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

        lli res = 0;

        lli remainMinus = 0;
        lli remainPlus = 0;

        for(int i = 0; i < n; i++) {
            if(a[i] > 0) {
                remainPlus += a[i];
            } else {
                remainPlus += a[i];
                if(remainPlus < 0) {
                    remainMinus += (-remainPlus);
                    remainPlus = 0;
                }
            }
        }

        cout << remainMinus << "\n";
    }

    return 0;
}
