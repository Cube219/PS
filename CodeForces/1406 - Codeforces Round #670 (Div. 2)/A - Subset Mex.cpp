#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n, a[101];
int cnt[101];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        for(int i = 0; i <= 100; i++) cnt[i] = 0;

        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            cnt[a[i]]++;
        }

        int idx1;
        for(int i = 0; i <= 100; i++) {
            if(cnt[i] < 2) {
                idx1 = i;
                break;
            }
        }

        int idx2;
        for(int i = idx1; i <= 100; i++) {
            if(cnt[i] == 0) {
                idx2 = i;
                break;
            }
        }

        cout << (idx1 + idx2) << endl;
    }

    return 0;
}
