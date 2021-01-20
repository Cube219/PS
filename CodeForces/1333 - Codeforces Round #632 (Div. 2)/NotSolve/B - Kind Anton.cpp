#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int tNum;
int n, a[100001], b[100001];

int main(void)
{
    scanf("%d", &tNum);
    
    for(int tt = 0; tt < tNum; tt++) {
        scanf("%d", &n);

        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }

        bool isPossible = true;
        for(int i = n - 1; i >= 0; i--) {
            if(a[i] == b[i]) continue;

            bool isMinus;
            if(b[i] - a[i] < 0) isMinus = true;
            else isMinus = false;

            int t = 0;
            for(int j = 0; j < i; j++) {
                if(isMinus && a[j] == -1) {
                    t = 1;
                    break;
                }
                if(!isMinus && a[j] == 1) {
                    t = 1;
                    break;
                }
            }
            if(t == 0) {
                isPossible = false;
                break;
            }
        }

        if(isPossible == true) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
