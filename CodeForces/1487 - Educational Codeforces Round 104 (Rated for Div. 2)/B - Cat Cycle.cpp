#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
ll n, k;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> k;
        k--;
        if(n % 2 == 0) {
            cout << k % n + 1 << "\n";
            continue;
        }
 
        ll gap = n / 2;
        if(k >= gap) {
            ll tmp = k - gap;
            k += tmp / gap + 1;
        }
        cout << k % n + 1 << "\n";
    }
 
    return 0;
}
