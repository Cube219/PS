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
int n;
string str;

string ss[13];

vector<int> fail;

void init_fail(const string& w)
{
    int wn = w.size();
    fail.clear();
    fail.resize(wn, 0);

    int j = 0;
    for(int i = 1; i < wn; ++i) {
        while(j > 0 && w[i] != w[j]) {
            j = fail[j - 1];
        }
        if(w[i] == w[j]) {
            fail[i] = j + 1;
            j++;
        }
    }
}

bool kmp(const string& s, const string& w)
{
    init_fail(w);

    int sn = s.size();
    int wn = w.size();

    int j = 0;
    for(int i = 0; i < sn; ++i) {
        while(j > 0 && s[i] != w[j]) {
            j = fail[j - 1];
        }
        if(s[i] == w[j]) {
            if(j == wn - 1) {
                return true;
                j = fail[j];
            } else {
                j++;
            }
        }
    }
    return false;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ss[1] = "L";
    for(int i = 2; i < 13; ++i) {
        string tmp = "L";
        for(int j = 0; j < ss[i - 1].size(); ++j) {
            tmp.push_back(ss[i - 1][j]);
            if(j % 2 == 0) tmp.push_back('R');
            else tmp.push_back('L');
        }
        ss[i] = tmp;
    }

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> str;
        if(n >= 12) n = 12;

        bool res = kmp(ss[n], str);

        cout << "Case " << tt << ": ";
        if(res == false) cout << "No\n";
        else cout << "Yes\n";
    }

    return 0;
}
