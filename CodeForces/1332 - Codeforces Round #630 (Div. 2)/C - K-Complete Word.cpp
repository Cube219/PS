#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, k;
char s[200001];

char tmp[200001];
int aNum[27];

int res;

int GetCost()
{
    int num = n / k;
    int cost = 0;
    for(int i = 0; i < num; i++) {
        int start = k * i;

        for(int j = 0; j < k; j++) {
            if(tmp[j] != s[start + j]) {
                cost++;
            }
        }
    }
    return cost;
}

int main(void)
{
    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        res = 2147483647;
        scanf("%d %d %s", &n, &k, s);

        int num = n / k;

        for(int i = 0; i <= k / 2; i++) {
            for(int i = 0; i < 27; i++) {
                aNum[i] = 0;
            }

            for(int j = 0; j < num; j++) {
                int start = j * k;
                aNum[s[start + i] - 'a']++;
                aNum[s[start + k - i - 1] - 'a']++;
            }

            int max = 0, maxA;
            for(int j = 0; j < 27; j++) {
                if(max < aNum[j]) {
                    max = aNum[j];
                    maxA = j;
                }
            }

            tmp[i] = tmp[k - i - 1] = maxA + 'a';
        }
        printf("%d\n", GetCost());
    }

    return 0;
}
