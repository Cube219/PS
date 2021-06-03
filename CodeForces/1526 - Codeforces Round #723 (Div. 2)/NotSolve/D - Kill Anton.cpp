#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

int tNum;
string str;
int nums[4];
int per[4];
ll res;
int resper[4];

char getch(int v)
{
    switch(v) {
        case 0: return 'A';
        case 1: return 'N';
        case 2: return 'O';
        case 3: return 'T';
        default: return 'A';
    }
}
int getchidx(char ch)
{
    switch(ch) {
        case 'A': return 0;
        case 'N': return 1;
        case 'O': return 2;
        case 'T': return 3;
        default: return -1;
    }
}

ll getnum(string& ss)
{
    string ss2 = ss;
    ll ret = 0;
    for(int i = 0; i < ss.size(); ++i) {
        int idx = i;
        for(int j = i; j < ss.size(); ++j) {
            if(str[i] == ss[j]) {
                idx = j;
                break;
            }
        }
        for(int j = idx - 1; j >= i; --j) {
            ret++;
            swap(ss[j], ss[j + 1]);
        }
    }
    ll ret2 = 0;
    for(int i = ss2.size() - 1; i >= 0; --i) {
        int idx = i;
        for(int j = i; j >= 0; --j) {
            if(str[i] == ss2[j]) {
                idx = j;
                break;
            }
        }
        for(int j = idx + 1; j <= i; ++j) {
            ret2++;
            swap(ss2[j - 1], ss2[j]);
        }
    }

    return min(ret, ret2);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> str;
        for(int i = 0; i < 4; ++i) {
            nums[i] = 0;
        }
        for(int i = 0; i < str.size(); ++i) {
            if(str[i] == 'A') nums[0]++;
            else if(str[i] == 'N') nums[1]++;
            else if(str[i] == 'O') nums[2]++;
            else nums[3]++;
        }

        for(int i = 0; i < 4; ++i) {
            per[i] = i;
        }
        string cur;
        res = 0;
        for(int i = 0; i < 24; ++i) {
            cur.clear();
            for(int j = 0; j < 4; ++j) {
                int ch = per[j];
                for(int k = 0; k < nums[ch]; ++k) {
                    cur.push_back(getch(ch));
                }
            }
            ll r = getnum(cur);
            if(r > res) {
                res = r;
                for(int j = 0; j < 4; ++j) {
                    resper[j] = per[j];
                }
            }
            next_permutation(per, per + 4);
        }
        cur.clear();
        for(int j = 0; j < 4; ++j) {
            int ch = resper[j];
            for(int k = 0; k < nums[ch]; ++k) {
                cur.push_back(getch(ch));
            }
        }
        cout << cur <<"\n";
    }

    return 0;
}
