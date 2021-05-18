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

int n;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool pos = true;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        string str;
        cin >> str;
        if(str[0] == 'm') continue;
        int a = stoi(str);
        if(a != i) {
            pos = false;
            break;
        }
    }
    if(pos == true) {
        cout << "makes sense";
    } else {
        cout << "something is fishy";
    }

    return 0;
}
