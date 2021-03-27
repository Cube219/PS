#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> g[301];
int a[301], b[301];
bool isComp[301];
bool bp(int cur)
{
    isComp[cur] = true;
    for(int nxt : g[cur]) {
        if(b[nxt] == -1) {
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

int n, m, num;
bool map[301][301];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> num;
    for(int i = 0; i < num; ++i) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        map[x][y] = true;
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == true) continue;
            g[i].push_back(j);
        }
    }

    for(int i = 0; i < n; ++i) {
        a[i] = -1;
    }
    for(int i = 0; i < m; ++i) {
        b[i] = -1;
    }
    int res = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] == -1) {
            for(int j = 0; j < n; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }

    cout << res;

    return 0;
}
