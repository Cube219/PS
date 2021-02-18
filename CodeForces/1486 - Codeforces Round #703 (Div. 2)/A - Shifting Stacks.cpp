#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n;
ll d[101];
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        ll sum = 0;
        ll s2 = 0;
 
        bool res = true;
 
        for(int i = 0; i < n; ++i) {
            ll a;
            cin >> a;
            sum += a;
            s2 += i;
            if(sum < s2) {
                res = false;
            }
        }
 
        if(s2 <= sum && res == true) cout << "YES\n";
        else cout << "NO\n";
    }
 
    return 0;
}
