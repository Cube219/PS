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

    string str;
    cin >> str;
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '.') {
            int v = str[i + 1] - '0';
            if(v <= 2) cout << "-";
            else if(v <= 6) {
                
            } else {
                cout << "+";
            }
            break;
        } else {
            cout << str[i];
        }
    }

    return 0;
}
