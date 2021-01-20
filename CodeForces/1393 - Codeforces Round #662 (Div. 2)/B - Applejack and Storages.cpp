#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <iostream>
using namespace std;

using lli = long long int;

int n;
int num[100001];
int eightNum, sixNum, fourNum, twoNum;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int d;
        scanf("%d", &d);

        if(num[d] == 3) twoNum--;
        else if(num[d] == 5) fourNum--;
        else if(num[d] == 7) sixNum--;

        num[d]++;

        if(num[d] == 2) twoNum++;
        else if(num[d] == 4) fourNum++;
        else if(num[d] == 6) sixNum++;
        else if(num[d] == 8) eightNum++;
    }

    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        char a[10];
        int b;
        scanf("%s %d", a, &b);

        if(a[0] == '+') {
            if(num[b] == 3) twoNum--;
            else if(num[b] == 5) fourNum--;
            else if(num[b] == 7) sixNum--;

            num[b]++;

            if(num[b] == 2) twoNum++;
            else if(num[b] == 4) fourNum++;
            else if(num[b] == 6) sixNum++;
            else if(num[b] == 8) eightNum++;
        } else {
            if(num[b] == 8) {
                eightNum--;
                sixNum++;
            } else if(num[b] == 6) {
                sixNum--;
                fourNum++;
            } else if(num[b] == 4) {
                fourNum--;
                twoNum++;
            } else if(num[b] == 2) {
                twoNum--;
            }

            num[b]--;
        }

        if(eightNum >= 1) {
            printf("YES\n");
        } else if(sixNum >= 2){
            printf("YES\n");
        } else if(fourNum >= 2) {
            printf("YES\n");
        } else if(fourNum >= 1 && sixNum >= 1) {
            printf("YES\n");
        } else if(fourNum >= 1 && twoNum >= 2) {
            printf("YES\n");
        } else if(sixNum >= 1 && twoNum >= 1) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
