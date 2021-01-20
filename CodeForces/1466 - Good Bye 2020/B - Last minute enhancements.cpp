#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, d[100001];
int res;
int d2[100001];
int cnt[100001];
int dl;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;
        dl = 0;

        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> d[i];
        }
        
        d[n - 1]++;
        for(int i = n - 2; i >= 0; i--) {
            if(d[i] + 1 < d[i + 1]) {
                d[i]++;
            }
        }

        res = 1;
        for(int i = 1; i < n; i++) {
            if(d[i - 1] != d[i]) res++;
        }

        cout << res + dl << "\n";
    }

    return 0;
}
