#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int x, y;
int xp, xm, yp, ym;
char str[100001];
int sl;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        xp = 0;
        xm = 0;
        yp = 0;
        ym = 0;
 
        cin >> x >> y >> str;
        sl = strlen(str);
        for(int i = 0; i < sl; ++i) {
            if(str[i] == 'R') {
                xp++;
            }
            if(str[i] == 'L') {
                xm++;
            }
            if(str[i] == 'U') {
                yp++;
            }
            if(str[i] == 'D') {
                ym++;
            }
        }
 
        bool res = true;
        if(x < 0) {
            x = -x;
            if(x > xm) res = false;
        } else {
            if(x > xp) res = false;
        }
        if(y < 0) {
            y = -y;
            if(y > ym) res = false;
        } else {
            if(y > yp) res = false;
        }
 
        if(res == false) cout << "NO\n";
        else cout << "YES\n";
    }
 
    return 0;
}
