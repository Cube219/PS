#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <algorithm>

int n, k, d[200001];
int count[200001], gap[200001];

int main(void)
{
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &d[i]);
    }

    std::sort(d, d + n);

    int currentNum = d[0], ci = 0;
    count[0] = 1;
    for(int i = 1; i < n; i++) {
        if(currentNum != d[i]) {
            gap[ci] = d[i] - currentNum;
            currentNum = d[i];
            ci++;
        }
        count[ci]++;
    }
    int cNum = ci + 1;

    int res = 2147483647;

    int currentCount = count[0], currentCost = 0;
    for(int i = 0; i < cNum - 1; i++) {
        if(currentCount >= k) break;
        currentCost += gap[i] * currentCount;
        currentCount += count[i + 1];
    }

    if(res > currentCost) res = currentCost;

    currentCount = count[cNum - 1];
    currentCost = 0;
    for(int i = cNum - 2; i >= 0; i--) {
        if(currentCount >= k) break;
        currentCost += gap[i] * currentCount;
        currentCount += count[i + 1];
    }

    if(res > currentCost) res = currentCost;

    int firstCount = count[0];
    int lastCount = count[cNum - 1];
    int firstI = 0;
    int lastI = cNum - 2;
    currentCost = 0;

    while(firstI != lastI) {
        int firstCost = gap[firstI] * firstCount;
        int lastCost = gap[lastI] * lastCount;

        if(firstCost < lastCost) {
            currentCost += firstCost;
            firstCount += count[firstI + 1];
            firstI++;
        } else {
            currentCost += lastCost;
            lastCount += count[lastI + 1];
            lastI--;
        }
    }

    if(firstCount > lastCount) {
        currentCost += gap[lastI] * (k - firstCount);
    } else {
        currentCost += gap[firstI] * (k - lastCount);
    }
    
    if(res > currentCost) res = currentCost;

    printf("%d", res);

    return 0;
}