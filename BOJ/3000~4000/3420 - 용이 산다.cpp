#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <set>

using lli = long long int;

int tNum;
int n, m;
int d[1000001];
std::set<int> zeros;
int idx[1000001];
int res[1000001];

int main(void)
{
   freopen("input.txt", "r", stdin);
   freopen("ouput.txt", "w", stdout);

    scanf("%d", &tNum);

    for(int tt = 0; tt < tNum; tt++) {
        bool isPossible = true;

        zeros.clear();

        scanf("%d %d", &n, &m);

        for(int i = 1; i <= m; i++) {
            scanf("%d", &d[i]);
        }

        for(int i = 1; i <= n; i++) {
            idx[i] = -1;
        }
        for(int i = 1; i <= m; i++) {
            res[i] = 0;
        }

        for(int i = 1; i <= m; i++) {
            if(d[i] == 0) {
                zeros.insert(i);
            } else {
                auto findIter = zeros.upper_bound(idx[d[i]]);
                if(findIter == zeros.end()) {
                    isPossible = false;
                    break;
                }

                res[*findIter] = d[i];
                idx[d[i]] = i;
                zeros.erase(findIter);
            }
        }

        if(isPossible == false) {
            printf("NO\n");
        } else {
            printf("YES\n");
            for(int i = 1; i <= m; i++) {
                if(d[i] == 0) printf("%d ", res[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
