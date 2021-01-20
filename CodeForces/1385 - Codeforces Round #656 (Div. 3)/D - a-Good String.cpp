#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n;
char d[200001];

int process(int s, int e, char c, int n)
{
    if(s == e) {
        if(d[s] != c) return 1;
        else return 0;
    } else {
        int m = (s + e) / 2;
        // Left
        int l = 0;
        for(int i = s; i <= m; i++) {
            if(d[i] != c) l++;
        }

        // Right
        int r = 0;
        for(int i = m + 1; i <= e; i++) {
            if(d[i] != c) r++;
        }


        l += process(m + 1, e, c + 1, n * 2 + 1);
        r += process(s, m, c + 1, n * 2);

        if(l < r) return l;
        else return r;
    }
}

int main(void)
{
    freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d %s", &n, d);

        printf("%d\n", process(0, n - 1, 'a', 1));
    }

    return 0;
}
