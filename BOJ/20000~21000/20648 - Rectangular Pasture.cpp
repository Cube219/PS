#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Point
{
    int x, y;
};

int n;
vector<int> xx, yy;
Point d[3001];
int sum[3001][3001];

int getx(int v)
{
    return lower_bound(xx.begin(), xx.end(), v) - xx.begin();
}
int gety(int v)
{
    return lower_bound(yy.begin(), yy.end(), v) - yy.begin();
}

int getnum(int x1, int y1, int x2, int y2)
{
    return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        d[i] = { a, b };
        xx.push_back(a);
        yy.push_back(b);
    }
    sort(xx.begin(), xx.end());
    xx.erase(unique(xx.begin(), xx.end()), xx.end());
    sort(yy.begin(), yy.end());
    yy.erase(unique(yy.begin(), yy.end()), yy.end());
    for(int i = 0; i < n; ++i) {
        d[i].x = getx(d[i].x);
        d[i].y = gety(d[i].y);
        sum[d[i].x][d[i].y]++;
    }
    sort(d, d + n, [](const Point& l, const Point& r) {
        return l.x < r.x;
    });
    for(int i = 1; i < n + 1; ++i) {
        sum[0][i] += sum[0][i - 1];
        sum[i][0] += sum[i - 1][0];
    }
    for(int i = 1; i < n + 1; ++i) {
        for(int j = 1; j < n + 1; ++j) {
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }

    ll res = 0;
    for(int i = 0; i < n - 1; ++i) {
        for(int j = i + 1; j < n; ++j) {
            res++;

            int upy = d[i].y;
            int downy = d[j].y;
            if(upy < downy) swap(upy, downy);

            int upNum = getnum(d[i].x + 1, upy + 1, d[j].x - 1, n);
            int downNum = getnum(d[i].x + 1, 0, d[j].x - 1, downy - 1);
            res += upNum;
            res += downNum;
            res += (ll)upNum * downNum;
        }
    }

    cout << res + n + 1;

    return 0;
}
