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
    getline(cin, str);
    bool res = false;
    for(int i = 0; i < str.size() - 1; ++i) {
        if((str[i] == 'd' || str[i] == 'D') && str[i + 1] == '2') {
            res = true;
            break;
        }
    }
    if(res == true) cout << "D2";
    else cout << "unrated";

    return 0;
}
