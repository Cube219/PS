#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
char str[201], str2[201];
char s[2] = { '(', ')' };
int sl;
bool res = false;
 
bool ck()
{
    int num = 0;
    for(int i = 0; i < sl; ++i) {
        if(str2[i] == '(') {
            num++;
        } else {
            num--;
            if(num < 0) return false;
        }
    }
    if(num == 0) return true;
    else return false;
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> str;
        sl = strlen(str);
        res = false;
 
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                for(int k = 0; k < 2; ++k) {
                    for(int z = 0; z < sl; ++z) {
                        if(str[z] == 'A') {
                            str2[z] = s[i];
                        } else if(str[z] == 'B') {
                            str2[z] = s[j];
                        } else {
                            str2[z] = s[k];
                        }
                    }
                    if(ck() == true) {
                        res = true;
                        break;
                    }
                }
            }
        }
 
        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }
 
    return 0;
}
