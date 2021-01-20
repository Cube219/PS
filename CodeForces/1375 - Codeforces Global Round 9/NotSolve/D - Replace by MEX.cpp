#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, a[1001];
bool isUsed[1001];
bool isFinished;
int res[1001];

int GetMex()
{
    for(int i = 0; i <= 1000; i++) isUsed[i] = false;
    for(int i = 0; i < n; i++) {
        isUsed[a[i]] = true;
    }

    for(int i = 0; i <= 1000; i++) {
        if(isUsed[i] == false) return i;
    }
    return 1001;
}

bool isValid()
{
    for(int i = 1; i < n; i++) {
        if(a[i - 1] > a[i]) return false;
    }
    return true;
}

void BT(int cnt)
{
    for(int i = 0; i < cnt; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
    if(cnt > n * 2) return;

    if(isValid() == true) {
        printf("%d\n", cnt);
        for(int i = 0; i < cnt; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
        isFinished = true;

        return;
    }

    int mex = GetMex();
    int tmp;
    for(int i = 0; i < n; i++) {
        tmp = a[i];
        a[i] = mex;

        res[cnt] = i;

        BT(cnt + 1);

        a[i] = tmp;

        if(isFinished == true) return;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        isFinished = false;
        BT(0);
    }

    return 0;
}
