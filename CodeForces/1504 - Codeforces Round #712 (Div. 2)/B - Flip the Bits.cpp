#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n;
char s1[300002], s2[300002];
int n0, n1;
bool invert;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> s1 >> s2;
        invert = false;
        n0 = 0; n1 = 0;
        for(int i = 0; i < n; ++i) {
            if(s1[i] == '0') n0++;
            else n1++;
        }
        bool res = true;
        for(int i = n - 1; i >= 0; --i) {
            if(invert == false && s1[i] == s2[i]) {
                if(s1[i] == '0') {
                    n0--;
                } else {
                    n1--;
                }
                continue;
            }
            if(invert == true && s1[i] != s2[i]) {
                if(s1[i] == '0') {
                    n0--;
                } else {
                    n1--;
                }
                continue;
            }
            if(n0 != n1) {
                res = false;
                break;
            }
            invert = !invert;
            if(s1[i] == '0') {
                n0--;
            } else {
                n1--;
            }
        }

        if(res == true) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
