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

    auto cvt = [&](char ch) {
        switch(ch) {
            case 'A':
                cout << "a";
                break;
            case 'B':
                cout << "v";
                break;
            case 'E':
                cout << "ye";
                break;
            case 'K':
                cout << "k";
                break;
            case 'M':
                cout << "m";
                break;
            case 'H':
                cout << "n";
                break;
            case 'O':
                cout << "o";
                break;
            case 'P':
                cout << "r";
                break;
            case 'C':
                cout << "s";
                break;
            case 'T':
                cout << "t";
                break;
            case 'Y':
                cout << "u";
                break;
            case 'X':
                cout << "h";
                break;
        }
    };

    for(char ch : str) {
        cvt(ch);
    }

    return 0;
}
