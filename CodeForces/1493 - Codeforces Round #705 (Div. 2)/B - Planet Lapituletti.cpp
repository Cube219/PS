#define _CRT_SECURE_NO_WARNINGS 1
 
#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
 
using ll = long long int;
 
int tNum;
int h, m;
char str[101];
int ch, cm;
 
int conv[] = { 0, 1, 5, -1, -1, 2, -1, -1, 8, -1 };
 
 
bool ck(int hh, int mm)
{
    int rh = 0;
    int rm = 0;
 
    for(int i = 0; i < 2; ++i) {
        rh *= 10;
        int t = conv[mm % 10];
        if(t == -1) return false;
        rh += t;
        mm /= 10;
    }
    for(int i = 0; i < 2; ++i) {
        rm *= 10;
        int t = conv[hh % 10];
        if(t == -1) return false;
        rm += t;
        hh /= 10;
    }
 
    if(rh >= h || rm >= m) return false;
 
    return true;
}
 
int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> h >> m;
        cin >> str;
        int sl = strlen(str);
        ch = 0;
        cm = 0;
 
        int i;
        for(i = 0; i < sl; ++i) {
            if(str[i] == ':') {
                i++;
                break;
            }
            ch *= 10;
            ch += str[i] - '0';
        }
        for(; i < sl; ++i) {
            cm *= 10;
            cm += str[i] - '0';
        }
 
        while(1) {
            if(ck(ch, cm) == true) {
                break;
            }
            cm++;
            if(cm >= m) {
                ch++;
                cm -= m;
            }
            if(ch >= h) {
                ch = 0;
            }
        }
 
        if(ch < 10) cout << "0" << ch;
        else cout << ch;
        cout << ":";
        if(cm < 10) cout << "0" << cm;
        else cout << cm;
        cout << "\n";
    }
 
    return 0;
}
