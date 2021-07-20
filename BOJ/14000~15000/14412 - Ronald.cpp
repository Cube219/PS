#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, m;
int g[1001][1001], g2[1001][1001];

void cp()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            g2[i][j] = g[i][j];
        }
    }
}

bool ck()
{
    for(int i = 1; i < n; ++i) {
        if(g2[0][i] == 0) {
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                g2[i][j] = 1 - g2[i][j];
                g2[j][i] = 1 - g2[j][i];
            }
        }
    }

    bool res = true;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            if(g2[i][j] == 0) {
                res = false;
                break;
            }
        }
        if(res == false) break;
    }
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a][b] = 1;
        g[b][a] = 1;
    }

    bool res = false;
    // 자기자신 안 누르는 경우
    cp();
    if(ck() == true) res = true;

    // 자기자신 누르는 경우
    cp();
    for(int i = 1; i < n; ++i) {
        if(g2[0][i] == 1) {
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                g[i][j] = 1 - g[i][j];
                g[j][i] = 1 - g[j][i];
            }
        }
    }
    if(ck() == true) res = true;

    if(res == true) cout << "DA";
    else cout << "NE";

    return 0;
}
