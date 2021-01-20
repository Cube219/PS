#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <algorithm>
using namespace std;

int tNum;
int n, k, a[31], b[31];

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %d", &n, &k);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        for(int i = 0; i < n; i++) scanf("%d", &b[i]);

        sort(a, a + n);
        sort(b, b + n);

        for(int i = 0; i < k; i++) {
            if(a[i] >= b[n-i-1]) break;
            swap(a[i], b[n - i - 1]);
        }

        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += a[i];
        }
        printf("%d\n", sum);
    }

    return 0;
}
