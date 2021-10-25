#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int tNum;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        string str;
        cin >> str;

        char mn = str[0];
        for(char ch : str) mn = min(ch, mn);
        cout << mn << " ";
        for(char ch : str) {
            if(ch == mn) {
                mn = 0;
                continue;
            }
            cout << ch;
        }
        cout << "\n";
    }

    return 0;
}
