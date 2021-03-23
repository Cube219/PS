#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <memory.h>
using namespace std;

using ll = long long int;

int n, m, k;
vector<int> g[2002];

bool isComp[2002];
int a[2002], b[1002];

bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == 0) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt]);
            if(f == true) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }
    }
    return false;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i) {
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int tt;
            cin >> tt;
            g[i * 2].push_back(tt);
            g[i * 2 + 1].push_back(tt);
        }
    }

    int res = 0;
    for(int i = 2; i <= n * 2 + 1; i += 2) {
        if(a[i] == 0) {
            memset(isComp, 0, sizeof(bool) * n * 2 + 1);
            if(bp(i) == true) res++;
        }
    }
    int res2 = 0;
    for(int i = 3; i <= n * 2 + 1; i += 2) {
        if(a[i] == 0) {
            memset(isComp, 0, sizeof(bool) * n * 2 + 1);
            if(bp(i) == true) res2++;
            if(res2 >= k) break;
        }
    }

    cout << res + res2;

    return 0;
}
