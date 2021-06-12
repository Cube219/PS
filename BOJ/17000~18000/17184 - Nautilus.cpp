#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <bitset>
#include <string>
using namespace std;

using ll = long long int;

int r, c, m;
bitset<260000> map;
bitset<260000> cur;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> r >> c >> m;
    for(int i = 0; i < r; ++i) {
        string str;
        cin >> str;
        for(int j = 0; j < c; ++j) {
            if(str[j] == '.') map.set(i * (c + 2) + j + 1);
        }
    }
    cur = map;

    string str;
    cin >> str;
    for(int i = 0; i < m; ++i) {
        if(str[i] == 'N') {
            cur = cur >> (c + 2);
        } else if(str[i] == 'E') {
            cur = cur << 1;
        } else if(str[i] == 'S') {
            cur = cur << (c + 2);
        } else if(str[i] == 'W') {
            cur = cur >> 1;
        } else {
            cur = (cur >> (c + 2)) | (cur << 1) | (cur << (c + 2)) | (cur >> 1);
        }
        cur = cur & map;
    }

    int res = 0;
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(cur.test(i * (c + 2) + j + 1) == true) res++;
        }
    }
    cout << res;

    return 0;
}
