#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
 
using ll = long long int;
 
int tNum;
int n, k;
int r1, r2, r3;
int num;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        num = 0;
        cin >> n >> k;
        while(k > 3) {
            k--;
            n--;
            num++;
        }
        if(n % 2 == 1) {
            r1 = 1;
            r2 = n / 2;
            r3 = n / 2;
        } else {
            if((n / 2) % 2 == 0) {
                r1 = n / 2;
                r2 = r1 / 2;
                r3 = r1 / 2;
            } else {
                r1 = n / 2 - 1;
                r2 = r1;
                r3 = 2;
            }
        }
 
        cout << r1 << " " << r2 << " " << r3<<" ";
        for(int i = 0; i < num; ++i) {
            cout << "1 ";
        }
        cout<< "\n";
    }
 
    return 0;
}
