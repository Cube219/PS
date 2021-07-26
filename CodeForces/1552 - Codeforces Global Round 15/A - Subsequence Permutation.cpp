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

int tNum;
int n;
string s1, s2;
int num[30];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        for(int i = 0; i < 30; ++i) {
            num[i] = 0;
        }
        cin >> n >> s1;
        s2.clear();
        for(int i = 0; i < n; ++i) {
            num[s1[i] - 'a']++;
        }
        for(int i = 0; i < 30; ++i) {
            if(num[i] > 0) {
                for(int j = 0; j < num[i]; ++j) {
                    s2.push_back(i + 'a');
                }
            }
        }

        int res = 0;
        for(int i = 0; i < n; ++i) {
            if(s1[i] != s2[i]) res++;
        }
        cout << res << "\n";
    }

    return 0;
}
