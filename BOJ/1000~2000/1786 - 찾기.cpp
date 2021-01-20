#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

string s, t;
vector<int> fail;
vector<int> res;

void get_fail(const string& w)
{
    int wNum = w.size();
    fail.resize(wNum, 0);

    int j = 0;
    for(int i = 1; i < wNum; i++) {
        while(j > 0 && w[i] != w[j]) {
            j = fail[j - 1];
        }
        if(w[i] == w[j]) {
            fail[i] = j + 1;
            j++;
        }
    }
}

void kmp(const string& s, const string& w)
{
    get_fail(w);

    res.clear();

    int sNum = s.size();
    int wNum = w.size();

    int j = 0;
    for(int i = 0; i < sNum; i++) {

        while(j > 0 && s[i] != w[j]) {
            j = fail[j - 1];
        }

        if(s[i] == w[j]) {
            if(j == wNum - 1) {
                res.push_back(i - wNum + 1);
                j = fail[j];
            } else {
                j++;
            }
        }
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getline(cin, s);
    getline(cin, t);

    kmp(s, t);

    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] + 1 << "\n";
    }

    return 0;
}
