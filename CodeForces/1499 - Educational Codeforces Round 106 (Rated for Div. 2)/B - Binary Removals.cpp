#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
 
using ll = long long int;
 
int tNum;
char str[202];
bool res;
int strl;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = true;
 
        cin >> str;
        strl = strlen(str);
        int i = 0;
        for(i = 0; i < strl - 1; ++i) {
            if(str[i] == '1' && str[i + 1] == '1') {
                break;
            }
        }
        for(; i < strl - 1; ++i) {
            if(str[i] == '0' && str[i + 1] == '0') {
                res = false;
                break;
            }
        }
        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }
 
    return 0;
}
