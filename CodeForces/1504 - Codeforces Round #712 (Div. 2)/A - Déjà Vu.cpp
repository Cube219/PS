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
char str[300002];
int sl;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> str;
        sl = strlen(str);
        str[sl] = 'a';
        bool pos = false;
        for(int i = 0; i <= sl; ++i) {
            int j = sl - i;
            if(i >= j) break;
            if(str[i] != str[j]) {
                pos = true;
                break;
            }
        }
        if(pos == true) {
            cout << "YES\n";
            str[sl+1] = '\0';
            cout << str << "\n";
            continue;
        }
        for(int i = sl - 1; i >= 0; --i) {
            str[i + 1] = str[i];
        }
        str[0] = 'a';
        for(int i = 0; i <= sl; ++i) {
            int j = sl - i;
            if(i >= j) break;
            if(str[i] != str[j]) {
                pos = true;
                break;
            }
        }
        if(pos == true) {
            cout << "YES\n";
            str[sl + 1] = '\0';
            cout << str << "\n";
            continue;
        }
        cout << "NO\n";
    }

    return 0;
}
