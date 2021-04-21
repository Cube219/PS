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

void init_fail(const vector<int>& w)
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

void kmp(const vector<int>& s, const vector<int>& w, vector<int>& res)
{
    init_fail(w);
    res.clear();

    int sn = s.size();
    int wn = w.size();

    int j = 0;
    for(int i = 0; i < sn; ++i) {
        while(j > 0 && s[i] != w[j]) {
            j = fail[j - 1];
        }
        if(s[i] == w[j]) {
            if(j == wn - 1) {
                res.push_back(i - wn + 1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }
}

int n, k;
vector<int> mxstr;
int mxIdx, mxNum;
vector<vector<int>> strs;
vector<int> target;
bool has[101];
vector<int> tmp;
bool pos;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    strs.resize(n);
    for(int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        strs[i].resize(num);
        for(int j = 0; j < num; ++j) {
            cin >> strs[i][j];
        }
        if(num > mxNum) {
            mxIdx = i;
            mxNum = num;
        }
    }
    mxstr.resize(strs[mxIdx].size());
    mxstr.assign(strs[mxIdx].begin(), strs[mxIdx].end());

    target.resize(k);
    for(int i = 0; i < mxstr.size() - k + 1; ++i) {
        for(int j = 0; j < k; ++j) {
            target[j] = mxstr[i + j];
        }
        for(int j = 0; j < n; ++j) {
            has[j] = false;
        }
        for(int j = 0; j < n; ++j) {
            if(j == mxIdx) continue;
            kmp(strs[j], target, tmp);
            if(tmp.size() > 0) has[j] = true;
        }
        reverse(target.begin(), target.end());
        for(int j = 0; j < n; ++j) {
            if(j == mxIdx || has[j] == true) continue;
            kmp(strs[j], target, tmp);
            if(tmp.size() > 0) has[j] = true;
        }
        bool f = true;
        for(int j = 0; j < n; ++j) {
            if(j == mxIdx) continue;
            if(has[j] == false) {
                f = false;
                break;
            }
        }
        if(f == true) {
            pos = true;
            break;
        }
    }

    if(pos == true) cout << "YES";
    else cout << "NO";

    return 0;
}
