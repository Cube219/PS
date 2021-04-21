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

int gcd(int a, int b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

int n;
string s1, s2;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    s1.resize(n); s2.resize(n * 2);
    for(int i = 0; i < n; ++i) {
        char ch;
        cin >> ch;
        s1[i] = ch;
    }
    for(int i = 0; i < n; ++i) {
        char ch;
        cin >> ch;
        s2[i] = ch;
    }
    for(int i = 0; i < n; ++i) {
        s2[i + n] = s2[i];
    }
    s2.pop_back();
    vector<int> res;
    kmp(s2, s1, res);

    int a = res.size();
    int b = n;
    int div = gcd(a, b);
    a /= div;
    b /= div;
    cout << a << "/" << b;

    return 0;
}
