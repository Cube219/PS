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

vector<int> fail;

void initFail(const string& w)
{
    fail.clear();
    int wn = w.size();
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

void kmp(const string& s, const string& w, vector<int>& res)
{
    res.clear();
    initFail(w);
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

string s1, s2;
int n;
vector<int> idx;
int dp[100005];
bool has[100005][501];
int lens[501];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> s1 >> n;
    int s1l = s1.size();
    for(int i = 0; i < n; ++i) {
        cin >> s2;
        kmp(s1, s2, idx);
        int s2l = s2.size();
        lens[i] = s2l;
        for(int j = 0; j < idx.size(); ++j) {
            has[idx[j] + s2l][i] = true;
        }
    }
    for(int i = 1; i <= s1l; ++i) {
        dp[i] = dp[i - 1];
        for(int j = 0; j < n; ++j) {
            if(has[i][j] == true) {
                dp[i] = max(dp[i], dp[i - lens[j]] + lens[j]);
            }
        }
    }
    cout << dp[s1l];

    return 0;
}
