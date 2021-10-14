#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    char ch;
    int num;
};

int n;
Node d[51];
ll dp[51];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> d[i].ch >> d[i].num;
    }

    for(int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] * 2 + d[i].num;
    }

    ll res = dp[n];
    bool rev = true;

    for(int i = n; i >= 1; --i) {
        if(d[i].ch == 'R') {
            if(rev == false) {
                if(d[i].num > 1) {
                    res += d[i].num + dp[i - 1];
                    rev = true;
                    if(i == 1) res--;
                } else rev = false;
            } else rev = false;
        } else if(d[i].ch == 'B') {
            if(rev == true) {
                if(d[i].num > 1) {
                    res += d[i].num + dp[i - 1];
                    rev = true;
                    if(i == 1) res--;
                } else rev = false;
            } else rev = false;
        } else {
            rev = false;
        }
    }

    cout << res;

    return 0;
}
