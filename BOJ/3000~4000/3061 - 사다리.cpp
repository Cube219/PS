#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum, n, d[1001], s[1001];
int res = 0;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;

        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> d[i];
            s[i] = i + 1;
        }

        for(int i = 0; i < n; i++) {
            if(s[i] == d[i]) continue;

            int j;
            for(j = i + 1; j < n; j++) {
                if(d[i] == s[j]) break;
            }

            while(i != j) {
                swap(s[j - 1], s[j]);
                res++;
                j--;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
