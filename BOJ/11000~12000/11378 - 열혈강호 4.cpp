#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m, k;
vector<int> g[2002];
int curN;

bool isComp[2002];
int a[2002], b[1001];
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
            g[i].push_back(tt);
        }
    }
    curN = n;

    int res = 0;
    for(int i = 1; i <= n; ++i) {
        if(a[i] == 0) {
            for(int j = 1; j <= n; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }

    int res2 = 0;
    for(int i = 1; i <= n && k > 0; ++i) {
        g[curN + 1] = g[i];
        for(int j = 1; j <= curN; ++j) {
            isComp[j] = false;
        }
        if(bp(curN + 1) == true) {
            res2++;
            k--;
            curN++;
            i--;
        }
    }

    cout << res + res2;

    return 0;
}
