#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int n;
char str[104];
int sl;
char ch;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;
    ch = str[0];
    res = 1;
    for(int i = 1; i < n; i++) {
        cin >> str;
        if(str[0] != ch) {
            res = 0;
            break;
        }
    }

    cout << res;

    return 0;
}
