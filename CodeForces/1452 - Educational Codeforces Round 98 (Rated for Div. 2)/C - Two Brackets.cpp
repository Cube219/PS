#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using ll = long long int;

int tNum;
char str[200002];
int sl;
int r1, r2;
int cnt1, cnt2;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        r1 = 0;
        r2 = 0;
        cnt1 = 0;
        cnt2 = 0;

        cin >> str;
        sl = strlen(str);

        for(int i = 0; i < sl; i++) {
            if(str[i] == '(') {
                cnt1++;
            } else if(str[i] == ')') {
                if(cnt1 > 0) {
                    cnt1--;
                    r1++;
                }
            } else if(str[i] == '[') {
                cnt2++;
            } else { // ']'
                if(cnt2 > 0) {
                    cnt2--;
                    r2++;
                }
            }
        }
        
        cout << r1 + r2 << "\n";
    }

    return 0;
}
