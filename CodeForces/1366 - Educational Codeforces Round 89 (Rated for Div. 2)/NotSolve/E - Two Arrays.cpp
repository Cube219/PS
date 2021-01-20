#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <vector>
using namespace std;

int n, m, a[200001], b[200001];
// int d[200001][200001];

int p(int start, int bi)
{
    if(bi == m) return 1;

    bool isMin = false;
    int res = 0;
    for(int i = start; i < n; i++) {
        if(a[i] < b[bi]) break;
        if(n - i - 1 < m - bi - 1) break;

        if(a[i] == b[bi]) {
            isMin = true;
        }
        if(a[i] >= b[bi] && isMin == true) {
            res += p(i + 1, bi + 1);
        }
    }

    return res;
}

int main(void)
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }

    printf("%d", p(0, 0));

    return 0;
}
