#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[1001];
int res;

bool isComp[1001];
int a[1001], b[1001];

bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == 0) {
            b[nxt] = cur;
            a[cur] = nxt;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool r = bp(b[nxt]);
            if(r == true) {
                b[nxt] = cur;
                a[cur] = nxt;
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

    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        int num;
        cin >> num;
        for(int j = 0; j < num; ++j) {
            int a;
            cin >> a;
            g[i].push_back(a);
        }
    }

    for(int i = 1; i <= n; ++i) {
        if(a[i] == 0) {
            for(int j = 1; j <= n; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }

    cout << res;

    return 0;
}
