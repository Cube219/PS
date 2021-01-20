#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int k, n;
char ed[101], st[101], buf[101];
char res[101];
char sBuf[1002][101];
int sBufNum;

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> k >> n >> ed;
    for(int i = 0; i < k; i++) {
        st[i] = 'A' + i;
    }

    bool flag = false;
    for(int i = 0; i < n; i++) {
        cin >> buf;

        if(buf[0] == '?') {
            flag = true;
            continue;
        }

        if(flag == false) {
            for(int i = 0; i < k - 1; i++) {
                if(buf[i] == '-') {
                    swap(st[i], st[i + 1]);
                }
            }
        } else {
            for(int i = 0; i < k - 1; i++) {
                sBuf[sBufNum][i] = buf[i];
            }
            sBufNum++;
        }
    }

    for(int i = sBufNum - 1; i >= 0; i--) {
        for(int j = 0; j < k - 1; j++) {
            if(sBuf[i][j] == '-') {
                swap(ed[j], ed[j + 1]);
            }
        }
    }

    bool isFail = false;

    for(int i = 0; i < k - 1; i++) {
        if(st[i] == ed[i]) {
            res[i] = '*';
            continue;
        }

        if(st[i] != ed[i + 1])
        {
            isFail = true;
            break;
        }

        swap(st[i], st[i + 1]);
        res[i] = '-';
    }

    if(isFail == true) {
        for(int i = 0; i < k - 1; i++) {
            res[i] = 'x';
        }
    }
    res[k - 1] = '\0';

    cout << res;

    return 0;
}
