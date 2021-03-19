#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, k1, k2, w, b;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k1 >> k2 >> w >> b;
        int wl = min(k1, k2);
        int bl = max(k1, k2);
        bl = n - bl;
        wl += abs(k1 - k2) / 2;
        bl += abs(k1 - k2) / 2;
        w -= wl;
        b -= bl;
 
        if(w <= 0 && b <= 0) cout << "YES\n";
        else cout << "NO\n";
    }
 
    return 0;
}
