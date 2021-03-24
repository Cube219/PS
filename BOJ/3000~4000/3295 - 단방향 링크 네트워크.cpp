#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int tNum;
int n, m;
vector<int> g[1001];
int res;

bool isVisit[1001];
int a[1001], b[1001];
bool bp(int cur)
{
    isVisit[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == -1) {
            b[nxt] = cur;
            a[cur] = nxt;
            return true;
        } else if(isVisit[b[nxt]] == false) {
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

void init()
{
    for(int i = 0; i < n; ++i) {
        g[i].clear();
        a[i] = -1;
        b[i] = -1;
    }
    res = 0;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cin >> n >> m;
        init();
        for(int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
        }

        for(int i = 0; i < n; ++i) {
            if(a[i] == -1) {
                for(int j = 0; j < n; ++j) {
                    isVisit[j] = false;
                }
                if(bp(i) == true) res++;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
