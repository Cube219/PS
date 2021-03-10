#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, k;
char str[202];
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k >> str;
        if(k==0) {
            cout << "YES\n";
            continue;
        }
        int cnt = 0;
        for(int i = 0; i < n / 2; ++i) {
            if(str[i] != str[n - i - 1]) break;
            cnt++;
        }
        if(cnt > k) {
            cout << "YES\n";
        } else if(cnt == k) {
            if(k * 2 == n) cout << "NO\n";
            else cout << "YES\n";
        } else {
            cout << "NO\n";
        }
 
    }
 
    return 0;
}
