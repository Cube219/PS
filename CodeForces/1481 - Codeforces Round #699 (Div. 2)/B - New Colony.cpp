#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n, k;
int h[105];
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        for(int i = 0; i < n; ++i) {
            cin >> h[i];
        }

        for(int i = 0; i < k; ++i) {
            int j;
            for(j = 0; j < n - 1; ++j) {
                if(h[j] < h[j + 1]) {
                    h[j]++;
                    break;
                }
            }
            if(j == n - 1) {
                res = -1;
                break;
            } else if(i == k - 1) {
                res = j + 1;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
