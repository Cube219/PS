#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n;
char d[101][101];
int row[101][101], col[101][101];
int rowNum, colNum;

vector<int> g[6000];
int a[6000], b[6000];
bool isComp[6000];
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

void drawRow(int x, int y)
{
    rowNum++;
    for(int i = y; i <= n; ++i) {
        if(d[x][i] == 'X') return;
        row[x][i] = rowNum;
    }
}

void drawCol(int x, int y)
{
    colNum++;
    for(int i = x; i <= n; ++i) {
        if(d[i][y] == 'X') return;
        col[i][y] = colNum;
    }
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(d[i][j] == 'X') continue;

            if(row[i][j] == 0) drawRow(i, j);
            if(col[i][j] == 0) drawCol(i, j);
        }
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(d[i][j] == 'X') continue;

            g[row[i][j]].push_back(col[i][j]);
        }
    }

    int res = 0;
    for(int i = 1; i <= rowNum; ++i) {
        if(a[i] == 0) {
            for(int j = 1; j <= rowNum; ++j) {
                isComp[j] = false;
            }
            if(bp(i) == true) res++;
        }
    }

    cout << res;

    return 0;
}
