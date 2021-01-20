#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <vector>
using namespace std;

int tNum;
int n, p[100001];
vector<int> res;

int gMx, gIndex;

int main(void)
{
    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        res.clear();

        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
        }
        
        res.push_back(p[0]);
        for(int i = 1; i < n - 1; i++) {
            if((p[i - 1] < p[i] && p[i] < p[i + 1]) || (p[i - 1] > p[i] && p[i] > p[i + 1])) {
                continue;
            }
            res.push_back(p[i]);
        }
        res.push_back(p[n - 1]);

        printf("%d\n", res.size());
        for(int i = 0; i < res.size(); i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
    }

    return 0;
}
