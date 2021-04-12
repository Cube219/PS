#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, k;
char str[200005];
bool finish;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    int idx = 0;
    if(k == 1) {
        for(int i = 0; i < n; ++i) {
            str[i] = 'a';
        }
    } else {
        while(1) {
            for(int i = 0; i < k; ++i) {
                str[idx++] = 'a' + i;
                if(idx == n) {
                    finish = true;
                    break;
                }
                for(int j = i + 1; j < k; ++j) {
                    str[idx++] = 'a' + i;
                    if(idx == n) {
                        finish = true;
                        break;
                    }
                    str[idx++] = 'a' + j;
                    if(idx == n) {
                        finish = true;
                        break;
                    }
                }
                if(finish == true) break;
            }
            if(finish == true) break;
        }
    }

    str[n] = '\0';
    cout << str;

    return 0;
}
