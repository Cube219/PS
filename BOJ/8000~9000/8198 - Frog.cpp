#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll MAXN = 1000001;
constexpr ll INF = 9000000000000000000;

int n, k;
int g[MAXN][61];
ll m, p[MAXN];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k >> m;
    for(int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    p[n] = INF;

    int l = 0, r = k;
    g[0][0] = k;
    for(int i = 1; i < n; ++i) {
        while(r < i) {
            l++; r++;
        }
        while(p[r + 1] - p[i] < p[i] - p[l]) {
            l++;
            r++;
        }
        if(p[r] - p[i] > p[i] - p[l]) {
            g[i][0] = r;
        } else {
            g[i][0] = l;
        }
    }

    for(int j = 1; j <= 60; ++j) {
        for(int i = 0; i < n; ++i) {
            int nxt = g[i][j - 1];
            g[i][j] = g[nxt][j - 1];
        }
    }
    
    for(int i = 0; i < n; ++i) {
        ll mm = m;
        int cur = i;
        int mv = 0;
        while(mm > 0) {
            if((mm & 1) > 0) {
                cur = g[cur][mv];
            }
            mv++;
            mm >>= 1;
        }
        cout << cur + 1 << " ";
    }

    return 0;
}
