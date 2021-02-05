#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
ll n, k;
ll h[1005];
ll res;
 
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
 
        while(true) {
            int j;
            for(j = 0; j < n - 1; ++j) {
                if(h[j] < h[j + 1]) {
                    k -= (h[j + 1] - h[j]);
                    h[j] = h[j + 1];
                    break;
                }
            }
            if(k <= 0) {
                res = j + 1;
                break;
            }
            if(j == n - 1) {
                res = -1;
                break;
            }
        }
        if(res == n) res = -1;
        cout << res << "\n";
    }
 
    return 0;
}
