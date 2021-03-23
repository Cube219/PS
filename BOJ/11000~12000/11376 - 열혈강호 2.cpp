#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
vector<int> g[2002];
int res;

bool isComp[2002];
int a[2002], b[1002];
bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == 0) {
            b[nxt] = cur;
            a[cur] = nxt;
            return true;
        } else if(isComp[b[nxt]] == false) {
            bool f = bp(b[nxt]);
            if(f == true) {
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
            int tmp;
            cin >> tmp;
            g[i * 2].push_back(tmp);
            g[i * 2 + 1].push_back(tmp);
        }
    }

    for(int i = 2; i <= n * 2 + 1; ++i) {
        if(a[i] == 0) {
            for(int j = 2; j <= n * 2 + 1; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }
    cout << res;

    return 0;
}
