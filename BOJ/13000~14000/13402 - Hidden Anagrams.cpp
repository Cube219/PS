#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
using namespace std;

using ll = long long int;

set<vector<int>> s;
string s1, s2;
int res;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s1 >> s2;
    if(s1.size() > s2.size()) swap(s1, s2);

    vector<int> tmp;
    for(int sz = s1.size(); sz >= 1; --sz) {
        s.clear();
        tmp.clear();
        tmp.resize('z' - 'a' + 1, 0);
        int l = 0;
        int r = sz - 1;
        for(int i = l; i <= r; ++i) {
            tmp[s2[i] - 'a']++;
        }
        s.insert(tmp);
        while(r < s2.size() - 1) {
            tmp[s2[r + 1] - 'a']++;
            tmp[s2[l] - 'a']--;
            s.insert(tmp);
            l++;
            r++;
        }

        tmp.clear();
        tmp.resize('z' - 'a' + 1, 0);
        l = 0;
        r = sz - 1;
        for(int i = l; i <= r; ++i) {
            tmp[s1[i] - 'a']++;
        }
        while(r < s1.size()) {
            if(s.find(tmp) != s.end()) {
                res = sz;
                break;
            }
            if(r == s1.size() - 1) break;
            tmp[s1[r + 1] - 'a']++;
            tmp[s1[l] - 'a']--;
            l++;
            r++;
        }
        if(res > 0) break;
    }

    cout << res;

    return 0;
}
