#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

using lli = long long int;

int w, n;
int a[5001];
bool res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> w >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);
    for(int i = 0; i < n - 3; i++) {
        for(int j = i + 1; j < n - 2; j++) {
            // cout << i << " " << j << endl;
            int sum = a[i] + a[j];
            int remain = w - sum;

            if(remain <= 1 || remain >= 400000) continue;

            int l = j + 1;
            int r = n - 1;
            while(l < r) {
                int sum2 = a[l] + a[r];
                if(remain == sum2) {
                    res = true;
                    break;
                } else if(remain < sum2) {
                    r--;
                } else {
                    l++;
                }
            }
        }

        if(res == true) break;
    }

    if(res == true)cout << "YES";
    else cout << "NO";

    return 0;
}
