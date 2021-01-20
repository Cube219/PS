#define _CRT_SECURE_NO_WARNINGS 1

#include <cstdio>
#include <cstdlib>
#include <utility>
#include <algorithm>
using namespace std;

using lli = long long int;

int tNum;
int n, k;
pair<int, int> dot[10001];

int p(double h)
{
    int min = dot[0].second;
    int max = dot[0].second;
    int res = 1;

    double mid = (double)(min + max) / 2.0;

    for(int i = 1; i < n; i++) {
        if(min > dot[i].second) min = dot[i].second;
        if(max < dot[i].second) max = dot[i].second;

        if((double)(max - min) / 2 > h) {
            res++;
            min = dot[i].second;
            max = dot[i].second;
        }
    }

    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);

    scanf("%d", &tNum);
    for(int tt = 1; tt <= tNum; tt++) {
        scanf("%d %d", &n, &k);

        for(int i = 0; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            dot[i] = { x, y };
        }

        sort(dot, dot + n);

        double l = 0.0;
        double h = 200000000.0;
        while((h - l) > 0.0001) {
            double m = (l + h) / 2;

            int posK = p(m);

            if(posK > k) {
                l = m;
            } else {
                h = m;
            }
        }

        printf("%.1lf\n", l);
    }

    return 0;
}
