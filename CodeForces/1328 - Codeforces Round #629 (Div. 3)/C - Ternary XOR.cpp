#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int n;
char x[50001], a[50001], b[50001];

int main(void)
{
    int tn;
    scanf("%d", &tn);
    for(int tt = 0; tt < tn; tt++) {
        scanf("%d %s", &n, x);

        bool s = false;
        int i = 0;
        while(i < n) {
            if(x[i] == '1') {
                a[i] = '1';
                b[i] = '0';
                s = true;
                break;
            } else if(x[i] == '2') {
                a[i] = '1';
                b[i] = '1';
            } else {
                a[i] = '0';
                b[i] = '0';
            }
            i++;
        }
        for(int j = i + 1; j < n; j++) {
            a[j] = '0';
            b[j] = x[j];
        }

        a[n] = '\0';
        b[n] = '\0';

        printf("%s\n%s\n", a, b);
    }

    return 0;
}
