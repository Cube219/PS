#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
char str[101];
int sl;
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> str;
        sl = strlen(str);
 
        for(int i = 0; i < sl; ++i) {
            if(i%2==0) {
                if(str[i] == 'a') str[i] = 'b';
                else str[i] = 'a';
            } else {
                if(str[i] == 'z') str[i] = 'y';
                else str[i] = 'z';
            }
        }
 
        cout << str << "\n";
    }
 
    return 0;
}
