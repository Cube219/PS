#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <utility>
#include <vector>
#include <string.h>

using lli = long long int;

int tNum;
int n;
char s[200001];
int r[200001], rNum;

std::vector<int> zeroGroups;
std::vector<int> oneGroups;

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 0; tt < tNum; tt++) {
        rNum = 0;
        zeroGroups.clear();
        oneGroups.clear();

        scanf("%d %s", &n, s);

        for(int i = 0; i < n; i++) {
            int gNum = 0;
            if(s[i] == '0') {
                if(oneGroups.size() == 0) {
                    zeroGroups.push_back(++rNum);
                    gNum = rNum;
                } else {
                    gNum = oneGroups.back();
                    oneGroups.pop_back();
                    zeroGroups.push_back(gNum);
                }
            } else {
                if(zeroGroups.size() == 0) {
                    oneGroups.push_back(++rNum);
                    gNum = rNum;
                } else {
                    gNum = zeroGroups.back();
                    zeroGroups.pop_back();
                    oneGroups.push_back(gNum);
                }
            }
            r[i] = gNum;
        }


        printf("%d\n", rNum);
        for(int i = 0; i < n; i++) {
            printf("%d ", r[i]);
        }
        printf("\n");
    }

    return 0;
}
