#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

int n;
string str;
set<int> zero;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;
    n = str.size();
    for(int i = 0; i < n; ++i) {
        if(str[i] == '0') zero.insert(i);
    }
    zero.insert(-1);
    zero.insert(n);

    for(int i = 0; i < n; ++i) {
        if(str[i] == '2') {
            auto rit = zero.lower_bound(i);
            auto lit = prev(rit);
            int md = *rit + *lit - i;
            if(*lit != -1) {
                zero.erase(lit);
            }
            if(*rit != n) {
                zero.erase(rit);
            }
            zero.insert(md);

        }
    }
    for(int i = 0; i < n; ++i) {
        str[i] = '1';
    }
    for(auto idx : zero) {
        if(idx == -1 || idx == n) continue;
        str[idx] = '0';
    }

    cout << str;

    return 0;
}
