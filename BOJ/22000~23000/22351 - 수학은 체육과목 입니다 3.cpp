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

string str;

int ck(int v, int st)
{
    int cur = v + 1;
    string s;
    int idx = st;
    while(idx < str.size()) {
        s.clear();
        int tmp = cur;
        while(tmp > 0) {
            s.push_back(tmp % 10 + '0');
            tmp /= 10;
        }
        reverse(s.begin(), s.end());

        if(idx + s.size() > str.size()) return -1;

        for(int i = 0; i < s.size(); ++i) {
            if(s[i] != str[idx]) return -1;
            idx++;
        }

        cur++;
    }
    return cur - 1;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> str;
    int st = 0, ed = -1;
    for(int i = 0; i < str.size(); ++i) {
        st *= 10;
        st += str[i] - '0';

        ed = ck(st, i + 1);
        if(ed != -1) break;
    }

    cout << st << " " << ed;

    return 0;
}
