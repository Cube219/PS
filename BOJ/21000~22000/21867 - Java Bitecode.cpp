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

    cin >> n >> str;
    string res;
    for(int i = 0; i < n; ++i) {
        if(str[i] == 'J') continue;
        if(str[i] == 'A') continue;
        if(str[i] == 'V') continue;
        res.push_back(str[i]);
    }
    if(res.size() == 0) res = "nojava";
    cout << res;

    return 0;
}
