#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string.h>
using namespace std;

using ll = long long int;

int tNum;
char str[104];
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
        if(sl % 2 == 1) {
            cout << "NO\n";
            continue;
        }

        int stIdx, edIdx;
        for(int i = 0; i < sl; i++) {
            if(str[i] == '(') {
                stIdx = i;
            } else if(str[i] == ')') {
                edIdx = i;
            }
        }

        if(stIdx < edIdx) {
            cout << "YES\n";
        } else {
            if(edIdx == 0 || stIdx == sl - 1) cout << "NO\n";
            else cout << "YES\n";
        }

    }

    return 0;
}
