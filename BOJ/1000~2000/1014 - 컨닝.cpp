#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> g[101];
int a[101], b[101];
bool isComp[101];
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

int tNum;
int n, m;
char map[11][11];
int dx[] = { 0, -1, -1, 0 };
int dy[] = { -1, -1, 1, 1 };

int solve()
{
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> map[i];
    }
    for(int i = 0; i < n * m; ++i) {
        g[i].clear();
    }
    int res = 0;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(map[i][j] == 'x') continue;
            res++;
            int cNum = i * m + j;
            for(int k = 0; k < 4; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(map[nx][ny] == 'x') continue;
                int nNum = nx * m + ny;
                if(j % 2 == 0) {
                    g[cNum].push_back(nNum);
                } else {
                    g[nNum].push_back(cNum);
                }
            }
        }
    }

    for(int i = 0; i < n * m; ++i) {
        a[i] = -1;
    }
    for(int i = 0; i < n * m; ++i) {
        b[i] = -1;
    }
    int r2 = 0;
    for(int i = 0; i < n * m; ++i) {
        if(a[i] == -1) {
            for(int j = 0; j < n * m; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) r2++;
        }
    }
    res -= r2;
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        cout << solve() << "\n";
    }

    return 0;
}
