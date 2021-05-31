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

int num1[30], num2[30], sp1, sp2;
string s1, s2;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getline(cin, s1);
    getline(cin, s2);

    for(int i = 0; i < s1.size(); ++i) {
        if(s1[i] == ' ') sp1++;
        else num1[s1[i] - 'a']++;
    }
    for(int i = 0; i < s2.size(); ++i) {
        if(s2[i] == ' ') sp2++;
        else num2[s2[i] - 'a']++;
    }
    string res;
    if(sp1 < sp2) res.push_back(' ');
    for(int i = 0; i < 26; ++i) {
        if(num1[i] < num2[i]) res.push_back('a' + i);
    }
    cout << res;

    return 0;
}
