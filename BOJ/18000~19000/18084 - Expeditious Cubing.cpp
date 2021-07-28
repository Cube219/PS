#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int d[4], target;

int getv(const string& str)
{
    int res = 0;
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '.') continue;
        res *= 10;
        res += str[i] - '0';
    }
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string str;
    for(int i = 0; i < 4; ++i) {
        cin >> str;
        d[i] = getv(str);
    }
    cin >> str;
    target = getv(str);

    sort(d, d + 4);
    if(d[1] + d[2] + d[3] <= target * 3) {
        cout << "infinite";
        return 0;
    }
    if(d[0] + d[1] + d[2] > target * 3) {
        cout << "impossible";
        return 0;
    }

    int res = target * 3 - d[1] - d[2];
    cout << res / 100 << "." << (res / 10) % 10 << res % 10;

    return 0;
}
