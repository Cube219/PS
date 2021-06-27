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
string str;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        char ch;
        cin >> ch;
        str.push_back(ch);
    }

    int l = 0, r = n - 1;
    for(int i = 0; i < n; ++i) {
        int cl = l, cr = r;

        bool left = false;
        while(cl < cr) {
            if(str[cl] < str[cr]) {
                left = true;
                break;
            } else if(str[cl] > str[cr]) {
                left = false;
                break;
            }
            cl++;
            cr--;
        }
        if(left == true) {
            cout << str[l];
            l++;
        } else {
            cout << str[r];
            r--;
        }
        if((i + 1) % 80 == 0) cout << "\n";
    }

    return 0;
}
