#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tn;

int n, t[200001], r[200001];

int main(void)
{
    scanf("%d", &tn);

    for(int tt = 0; tt < tn; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &t[i]);
        }

        int lastColor = 1, colorCount = 1;
        r[0] = 1;
        for(int i = 1; i < n; i++) {
            if(t[i - 1] == t[i]) {
                r[i] = lastColor;
                continue;
            }

            colorCount = 2;
            if(lastColor == 1) {
                r[i] = 2;
                lastColor = 2;
            } else {
                r[i] = 1;
                lastColor = 1;
            }
        }

        if(t[0] != t[n - 1] && r[0] == r[n - 1]) {
            bool isSuccess = false;
            lastColor = r[n - 1];

            for(int i = 0; i < n - 1; i++) {
                if(lastColor == 1) {
                    r[i] = 2;
                    lastColor = 2;
                } else {
                    r[i] = 1;
                    lastColor = 1;
                }

                if(r[i] != r[i + 1]) {
                    isSuccess = true;
                    break;
                }
                if(t[i] == t[i + 1]) {
                    isSuccess = true;
                    break;
                }
            }

            if(isSuccess == false) {
                colorCount = 3;
                r[n - 1] = 3;
            }
        }

        printf("%d\n", colorCount);
        for(int i = 0; i < n; i++) {
            printf("%d ", r[i]);
        }
        printf("\n");
    }

    return 0;
}
