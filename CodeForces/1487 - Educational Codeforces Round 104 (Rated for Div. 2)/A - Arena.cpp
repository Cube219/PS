#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n;
int a[101];
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        sort(a, a + n);
        int cnt = 1;
        for(int i = 1; i < n; ++i) {
            if(a[i - 1] != a[i]) break;
            cnt++;
        }
        if(n == 1) cout << "1\n";
        else cout << n - cnt << "\n";
    }
 
    return 0;
}
