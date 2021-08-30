#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;

using ll = long long int;

int n;
set<pair<string, string>> mp;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    pair<string, string> s1;
    bool res = false;
    for(int i = 0; i < n; ++i) {
        cin >> s1.first >> s1.second;
        if(res == false) {
            auto it = mp.find(s1);
            if(it != mp.end()) {
                res = true;
            } else {
                mp.insert(s1);
            }
        }
    }
    if(res == true) cout << "Yes";
    else cout << "No";

    return 0;
}
