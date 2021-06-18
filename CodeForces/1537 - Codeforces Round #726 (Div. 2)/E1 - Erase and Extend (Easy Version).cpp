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

int n, m;
string str;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> str;

    int idx = n;
    for(int i = n - 1; i >= 1; --i) {
        int sz = i;
        bool pos = true;
        for(int j = 0; i + j < n; ++j) {
            if(str[j % sz] < str[i + j]) break;
            if(str[j % sz] > str[i+j]) {
                pos = false;
                break;
            }
        }
        if(pos == true) idx = i;
    }
    string str2;
    for(int i = 0; i < idx; ++i) {
        str2.push_back(str[i]);
    }
    for(int i = 0; i < m; ++i) {
        cout << str2[i % idx];
    }

    return 0;
}
