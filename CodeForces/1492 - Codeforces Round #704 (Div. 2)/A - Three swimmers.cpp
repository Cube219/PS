#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
ll p, a, b, c;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> p >> a >> b >> c;
 
        ll pa = a - (p % a);
        if(p % a == 0) pa = 0;
        ll pb = b - (p % b);
        if(p % b == 0) pb = 0;
        ll pc = c - (p % c);
        if(p % c == 0) pc = 0;
 
        ll r = pa;
        if(r > pb) {
            r = pb;
        }
        if(r > pc) {
            r = pc;
        }
        cout << r << "\n";
    }
 
    return 0;
}
