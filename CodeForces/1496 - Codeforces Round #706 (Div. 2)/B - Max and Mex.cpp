#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, k;
int d[100001];
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        for(int i = 0; i < n; ++i) {
            cin >> d[i];
        }
        sort(d, d + n);
        int mex = -1;
        for(int i = 0; i < n; ++i) {
            if(i != d[i]) {
                mex = i;
                break;
            }
        }
        if(mex == -1) mex = d[n - 1];
        int mx = d[n - 1];
 
        int t = (mex + mx) / 2;
        if((mex + mx) % 2 == 1) t++;
        bool has = false;
        for(int i = 0; i < n; ++i) {
            if(d[i] == t) {
                has = true;
                break;
            }
        }
 
        if(mex + 1 == mx) {
            cout << n << "\n";
        } else if(mex == mx) {
            cout << n + k << "\n";
        } else {
            if(has == false && k > 0) cout << n + 1 << "\n";
            else cout << n << "\n";
        }
    }
 
    return 0;
}
