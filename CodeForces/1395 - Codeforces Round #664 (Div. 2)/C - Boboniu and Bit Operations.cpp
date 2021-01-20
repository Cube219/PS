#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>

using lli = long long int;

int n, m, a[201], b[201], c[201], bb[201], tmpbb[201];

void cal(int& res)
{
    res = 0;
    for(int i = 0; i < n; i++) {
        res = (res | (a[i] & bb[i]));
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int bMin = 987654321;
    for(int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
        if(bMin > b[i]) bMin = b[i];
    }

    int res = 0;
    for(int i = 0; i < n; i++) {
        res = (res | (a[i] & bMin));
        bb[i] = bMin;
    }

    int setting = 0;

    int current = 1 << 11;
    while(current > 1) {
        current = current >> 1;
        if((res & current) == 0) continue;

        for(int i = 0; i < n; i++) tmpbb[i] = -1;

        bool isPossible = true;
        for(int i = 0; i < n; i++) {
            if((a[i] & current) == 0) continue;

            bool ck = false;
            for(int j = 0; j < m; j++) {
                if(((a[i] & b[j]) & ~setting) < current) {
                    ck = true;
                    tmpbb[i] = (a[i] & b[j]);
                    break;
                }
            }
            if(ck == false) {
                isPossible = false;
                break;
            }
        }

        if(isPossible == true) {
            for(int i = 0; i < n; i++) {
                if(tmpbb[i] != -1) {
                    bb[i] = tmpbb[i];
                }
            }
            cal(res);
        } else {
            setting = (setting | current);
        }
    }

    printf("%d", res);

    return 0;
}
