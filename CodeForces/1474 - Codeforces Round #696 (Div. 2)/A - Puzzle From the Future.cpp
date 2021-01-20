#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
int n;
char str[100003];
char res[100003];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> str;
        res[0] = '1';
        for(int i = 1; i < n; i++) {
            int a = str[i - 1] - '0';
            int b = res[i - 1] - '0';
            int c = str[i] - '0';
            if(a + b != c + 1) {
                res[i] = '1';
            } else {
                res[i] = '0';
            }
        }
        res[n] = '\0';
        cout << res<<"\n";
    }

    return 0;
}
