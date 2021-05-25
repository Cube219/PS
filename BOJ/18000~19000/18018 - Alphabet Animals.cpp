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
int has[30];
vector<string> d;
string res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string last;
    cin >> last >> n;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        has[d[i][0] - 'a']++;
    }
    bool pos = false;
    bool ex = false;
    char ch = last.back();
    for(int i = 0; i < n; ++i) {
        char cur = d[i][0];
        if(ch == cur) {
            if(pos == false) res = d[i];
            pos = true;
            has[cur - 'a']--;
            if(has[d[i].back() - 'a'] == 0) {
                ex = true;
                res = d[i];
                break;
            }
            has[cur - 'a']++;
        }
    }
    if(pos == false) cout << "?";
    else {
        cout << res;
        if(ex == true) cout << "!";
    }

    return 0;
}
    