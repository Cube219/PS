#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
using namespace std;

using lli = long long int;

int tNum;
int n, a[200001];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 0; tt < tNum; tt++) {
        lli res = 0;

        int max, min;

        cin >> n;
        cin >> a[0];
        max = a[0];
        min = 1000000001;
        for(int i = 1; i < n; i++) {
            cin >> a[i];

            if(a[i - 1] >= a[i]) {
                min = a[i];
                continue;
            }

            if(max <= a[i]) {
                if(min != 1000000001)
                    res += (lli)(max - min);

                max = a[i];
                min = 1000000001;
            } else {
                res += (lli)(a[i] - min);
                min = a[i];
            }
        }

        if(min != 1000000001)
            res += (lli)(max - min);

        cout << res << endl;
    }

    return 0;
}
