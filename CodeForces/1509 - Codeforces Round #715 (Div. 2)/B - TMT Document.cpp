#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
char str[100004];
int tnum, mnum;
bool pos;
int lastm;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> str;

        tnum = 0;
        mnum = 0;
        pos = true;
        for(int i = 0; i < n; ++i) {
            if(str[i] == 'T') {
                tnum++;
            } else {
                if(tnum <= mnum) pos = false;
                mnum++;
                lastm = i;
            }
        }
        tnum = 0;
        mnum = 0;
        for(int i = n - 1; i >= 0; --i) {
            if(str[i] == 'T') {
                tnum++;
            } else {
                if(tnum <= mnum) pos = false;
                mnum++;
                lastm = i;
            }
        }
        if(mnum * 2 != tnum) pos = false;

        if(pos == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
