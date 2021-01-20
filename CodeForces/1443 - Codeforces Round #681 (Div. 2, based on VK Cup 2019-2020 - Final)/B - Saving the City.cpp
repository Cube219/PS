#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <string.h>
using namespace std;

using ll = long long int;

int tNum;
int a, b;
char m[100002];
int mL;
int res;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> a >> b >> m;

        mL = strlen(m);

        int st = -1;
        for(int i = 0; i < mL; i++) {
            if(m[i] == '1') {
                st = i;
                break;
            }
        }

        if(st == -1) {
            cout << "0\n";
            continue;
        }

        res = a;
        int cnt = -1;
        int oneCnt = 1;
        bool isZero = false;
        for(int i = st + 1; i < mL; i++) {
            if(m[i] == '1') {
                if(isZero == true) {
                    oneCnt = 0;

                    isZero = false;
                }
                oneCnt++;
            } else {
                if(isZero == false) {
                    if(cnt != -1) {
                        if(a > cnt * b) {
                            res += cnt * b;
                        } else {
                            res += a;
                        }
                    }

                    isZero = true;
                    cnt = 0;
                    oneCnt = 0;
                }
                cnt++;
            }
        }
        if(isZero == false) {
            if(cnt != -1) {
                if(a > cnt * b) {
                    res += cnt * b;
                } else {
                    res += a;
                }
            }
        }

        cout << res << "\n";
    }

    return 0;
}
