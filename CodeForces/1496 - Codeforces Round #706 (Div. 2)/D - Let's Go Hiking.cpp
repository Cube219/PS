#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int n, d[100002];
int res;
int maxL;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    d[0] = 999999999;
    d[n + 1] = 999999999;
 
    for(int i = 2; i <= n - 1; ++i) {
        if(d[i - 1] > d[i] || d[i] < d[i + 1]) continue;
 
        int l = 1, r = 1;
        for(int j = i - 1; j >= 1; j--) {
            if(d[j] > d[j + 1]) break;
            l++;
        }
        for(int j = i + 1; j <= n; j++) {
            if(d[j - 1] < d[j]) break;
            r++;
        }
 
        int len = max(l, r);
 
        if(l == r && l % 2 == 1) {
            if(maxL < l) {
                res = 1;
                maxL = l;
            } else if(maxL == l) {
                res = 0;
            }
        } else {
            if(len >= maxL) {
                maxL = len;
                res = 0;
            }
        }
    }
 
    int cnt = 1;
    if(d[1] > d[2]) {
        for(int i = 2; i <= n; ++i) {
            if(d[i - 1] < d[i]) break;
            cnt++;
        }
        if(cnt >= maxL) res = 0;
    }
    
    cnt = 1;
    if(d[n - 1] < d[n]) {
        for(int i = n - 1; i >= 1; --i) {
            if(d[i] > d[i + 1]) break;
            cnt++;
        }
        if(cnt >= maxL) res = 0;
    }
 
    cout << res;
 
    return 0;
}
