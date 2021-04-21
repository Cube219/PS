#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> fail;

void initFail(const string& w)
{
    fail.clear();
    int wl = w.size();
    fail.resize(wl, 0);

    int j = 0;
    for(int i = 1; i < wl; ++i) {
        while(j > 0 && w[i] != w[j]) {
            j = fail[j - 1];
        }
        if(w[i] == w[j]) {
            fail[i] = j + 1;
            j++;
        }
    }
}

void kmp(const string& s, const string& w, vector<int>& res)
{
    int sl = s.size();
    int wl = w.size();
    res.clear();
    initFail(w);

    int j = 0;
    for(int i = 0; i < sl; ++i) {
        while(j > 0 && s[i] != w[j]) {
            j = fail[j - 1];
        }
        if(s[i] == w[j]) {
            if(j == wl - 1) {
                res.push_back(i - wl + 1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }
}

int tNum;
string alpa, ori, str, str2;
char table[202];
vector<int> res;
vector<int> idx;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> alpa >> ori >> str;
        str2.resize(ori.size());
        res.clear();

        int alpal = alpa.size();
        for(int i = 0; i < alpal; ++i) {
            for(int j = 0; j < alpal; ++j) {
                char a = alpa[j];
                char b = alpa[(j + i) % alpal];
                table[a] = b;
            }

            for(int i = 0; i < ori.size(); ++i) {
                str2[i] = table[ori[i]];
            }
            kmp(str, str2, idx);
            if(idx.size() == 1) {
                res.push_back(i);
            }
        }

        if(res.size() == 0) {
            cout << "no solution\n";
        } else if(res.size() == 1) {
            cout << "unique: " << res[0] << "\n";
        } else {
            cout << "ambiguous: ";
            for(int i = 0; i < res.size(); ++i) {
                cout << res[i] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}
