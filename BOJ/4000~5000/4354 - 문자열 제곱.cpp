#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
#include <string>
using namespace std;

using ll = long long int;

string s;
vector<int> fail;

void get_fail(const string& w)
{
    int wNum = w.size();
    fail.clear();
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

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while(1) {
        cin >> s;
        if(s[0] == '.') break;

        get_fail(s);

        int fNum = fail[s.size() - 1];
        int sNum = s.size();
        
        int res = -1;
        for(int i = sNum; i >= 1; i--) {
            ll l = (ll)sNum * (i - 1);
            ll r = i;
            if(l%r == 0 && l/r == fNum) {
                res = i;
                break;
            }
        }
        if(res == -1) res = 1;

        cout << res << "\n";
    }

    return 0;
}
