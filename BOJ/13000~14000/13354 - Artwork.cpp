#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Line
{
    int x1, y1, x2, y2;
};

int n, m, q;
int map[1005][1005];
bool isblack[1005][1005];
Line d[10001];
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };
int par[1000001];
int curnum;
int res[10001];

int find(int a)
{
    vector<int> st;
    while(par[a] != a) {
        st.push_back(a);
        a = par[a];
    }
    for(int i = 0; i < st.size(); ++i) {
        par[st[i]] = a;
    }
    return a;
}

void uni(int a, int b)
{
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) return;
    par[rb] = ra;
    curnum--;
}

int getnum(int x, int y)
{
    return y * n + x + 1;
}

void erase(int x, int y)
{
    isblack[x][y] = false;
    curnum++;
    int cnum = getnum(x, y);
    for(int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
        int nnum = getnum(nx, ny);

        if(isblack[nx][ny] == false) {
            uni(cnum, nnum);
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;
    curnum = n * m;
    for(int i = 0; i < q; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--; x2--; y2--;
        d[i] = { x1, y1, x2, y2 };
        if(x1 == x2) {
            for(int j = y1; j <= y2; ++j) {
                map[x1][j]++;
                if(isblack[x1][j] == false) curnum--;
                isblack[x1][j] = true;
            }
        } else {
            for(int j = x1; j <= x2; ++j) {
                map[j][y1]++;
                if(isblack[j][y1] == false) curnum--;
                isblack[j][y1] = true;
            }
        }
    }
    for(int i = 1; i <= n * m; ++i) {
        par[i] = i;
    }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < 4; ++k) {
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if(isblack[i][j] == true || isblack[nx][ny] == true) continue;
                uni(getnum(i, j), getnum(nx, ny));
            }
        }
    }
    res[q - 1] = curnum;
    for(int i = q - 1; i >= 1; --i) {
        int x1 = d[i].x1;
        int y1 = d[i].y1;
        int x2 = d[i].x2;
        int y2 = d[i].y2;
        if(x1 == x2) {
            for(int j = y1; j <= y2; ++j) {
                map[x1][j]--;
                if(map[x1][j] == 0) {
                    erase(x1, j);
                }
            }
        } else {
            for(int j = x1; j <= x2; ++j) {
                map[j][y1]--;
                if(map[j][y1] == 0) {
                    erase(j, y1);
                }
            }
        }
        res[i - 1] = curnum;
    }

    for(int i = 0; i < q; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
