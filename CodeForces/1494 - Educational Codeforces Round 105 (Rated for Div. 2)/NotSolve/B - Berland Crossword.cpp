#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int u, r, d, l, n;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> u >> r >> d >> l;
 
        if(u > 0 && r > 0) {
            u--;
            r--;
        }
        if(d > 0 && r > 0) {
            d--;
            r--;
        }
        if(d > 0 && l > 0) {
            d--;
            l--;
        }
        if(u > 0 && l > 0) {
            u--;
            l--;
        }
 
        n -= 2;
        if(u > n || d > n || l > n || r > n) cout << "NO\n";
        else cout << "YES\n";
    }
 
    return 0;
}
