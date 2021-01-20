#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string.h>
using namespace std;

using ll = long long int;

int tNum;
char str[5005];
char newStr[5005];
int n, sn, newN;
bool dp[5005][5005];
int leftC, rightC, res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        res = 0;
        newN = 0;

        cin >> str;
        n = strlen(str);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                dp[i][j] = false;
            }
        }

        for(sn = 0; sn < n / 2; sn++) {
            if(str[sn] != str[n - 1 - sn]) break;
        }

        for(int i = sn; i < n - sn; i++) {
            newStr[newN++] = str[i];
        }

        for(int i = 0; i < newN; i++) {
            dp[i][i] = true;
        }
        int maxL = 0, maxR = 0;
        for(int i = 0; i < newN - 1; i++) {
            if(newStr[i] == newStr[i + 1]) {
                dp[i][i + 1] = true;
            }
        }
        for(int l = 2; l < newN; l++) {
            for(int i = 0; i < newN - l; i++) {
                int j = i + l;
                if(newStr[i] == newStr[j] && dp[i+1][j-1] == true) {
                    dp[i][j] = true;
                }
            }
        }
        for(int i = 0; i < newN; i++) {
            if(dp[0][i] == true) {
                maxL = i + 1;
            }
        }
        for(int i = 0; i < newN; i++) {
            if(dp[newN - 1 - i][newN - 1] == true) {
                maxR = i + 1;
            }
        }

        for(int i = 0; i < sn; i++) {
            cout << str[i];
        }
        if(maxL > maxR) {
            for(int i = 0; i < maxL; i++) {
                cout << newStr[i];
            }
        } else {
            for(int i = 0; i < maxR; i++) {
                cout << newStr[newN - maxR + i];
            }
        }
        for(int i = 0; i < sn; i++) {
            cout << str[n - sn + i];
        }
        cout << "\n";
    }

    return 0;
}
