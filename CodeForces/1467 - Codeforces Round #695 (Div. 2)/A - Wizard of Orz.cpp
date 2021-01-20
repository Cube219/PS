#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
char str[200002];
int sl;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n;
        sl = 0;
        int idx = 9;

        if(n == 1) {
            str[sl++] = '9';
        } else {
            n -= 2;
            str[sl++] = '9';
            str[sl++] = '8';
            idx = 9;
            while(n > 0) {
                n--;
                str[sl++] = idx + '0';
                idx++;
                if(idx > 9) idx -= 10;
            }
        }
        str[sl] = '\0';
        cout << str << "\n";
    }

    return 0;
}
