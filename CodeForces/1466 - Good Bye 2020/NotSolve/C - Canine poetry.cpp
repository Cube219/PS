#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string.h>
using namespace std;

using ll = long long int;

int tNum;
char str[100002];
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

        int res = 0;

        for(int i = 1; i < sl; i++) {
            if(str[i - 1] == str[i]) {
                if(str[i] == str[i + 1]) {
                    str[i] = '0';
                    str[i - 1] = '0';
                    i += 2;
                    res += 2;
                } else {
                    str[i - 1] = '0';
                    res++;
                }
            }
        }

        for(int i = 2; i < sl; i++) {
            if(str[i - 2] == str[i] && str[i - 2] != '0' && str[i] != '0') {
                str[i - 2] = '0';
                str[i] = '0';
                res++;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
