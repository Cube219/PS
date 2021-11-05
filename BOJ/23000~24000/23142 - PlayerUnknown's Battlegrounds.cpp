#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 987654321;

int n, m;
int mp[305][305];
int d[305];
int res[90005];

void p(int uidx, int didx)
{
    if(uidx == didx) {
        res[d[uidx]]++;
        return;
    }
    int m = (uidx + didx) / 2;
    p(uidx, m);
    p(m + 1, didx);

    int curuidx = m;
    int curdidx = m + 1;
    int curu = d[curuidx];
    int curd = d[curdidx];
    int curmin = min(curu, curd);
    int unum = 1, dnum = 1;
    res[curmin]++;
    while(1) {
        int nxtu = -INF;
        if(curuidx > uidx) {
            nxtu = min(curu, d[curuidx - 1]);
        }
        int nxtd = -INF;
        if(curdidx < didx) {
            nxtd = min(curd, d[curdidx + 1]);
        }
        if(nxtu == -INF && nxtd == -INF) break;

        if(nxtu > nxtd) {
            // 위 확장
            curmin = min(curmin, nxtu);
            res[curmin] += dnum;
            curuidx--;
            unum++;
            curu = nxtu;
        } else {
            // 아래 확장
            curmin = min(curmin, nxtd);
            res[curmin] += unum;
            curdidx++;
            dnum++;
            curd = nxtd;
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

    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            cin >> mp[i][j];
        }
    }

    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            d[j] = INF;
        }
        for(int j = i; j < m; ++j) {
            for(int k = 0; k < n; ++k) {
                d[k] = min(d[k], mp[k][j]);
            }
            p(0, n - 1);
        }
    }

    for(int i = 1; i <= n * m; ++i) {
        cout << res[i] << "\n";
    }

    return 0;
}
