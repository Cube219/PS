#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

vector<int> g[20001];
int a[20001], b[20001];
bool isComp[20001];
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

int n, m;
bool map[101][101];
int d1Num, d2Num;
int d1[101][101], d2[101][101];

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        map[x][y] = true;
    }

    for(int i = 1; i <= n; ++i) {
        d1Num++;
        d2Num++;
        for(int j = 0; j < i; ++j) {
            int x = i - 1 - j;
            int y = j;
            if(map[x][y] == true) d1Num++;
            else d1[x][y] = d1Num;

            x = j;
            y = n - i + j;
            if(map[x][y] == true) d2Num++;
            else d2[x][y] = d2Num;
        }
    }

    for(int i = n - 1; i > 0; --i) {
        d1Num++;
        d2Num++;
        for(int j = 0; j < i; ++j) {
            int x = n - 1 - j;
            int y = j + (n - i);
            if(map[x][y] == true) d1Num++;
            else d1[x][y] = d1Num;

            x = n - 1 - j;
            y = i - 1 - j;
            if(map[x][y] == true) d2Num++;
            else d2[x][y] = d2Num;
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(map[i][j] == true) continue;
            g[d1[i][j]].push_back(d2[i][j]);
        }
    }

    for(int i = 0; i <= d1Num; ++i) {
        a[i] = -1;
    }
    for(int i = 0; i <= d2Num; ++i) {
        b[i] = -1;
    }
    int res = 0;
    for(int i = 1; i <= d1Num; ++i) {
        if(a[i] == -1) {
            for(int j = 1; j <= d1Num; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }

    cout << res;

    return 0;
}
