#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 2000000000;

struct Point
{
    ll l, r;
};
int n;
Point p[1000001];
ll res;

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
        p[i] = { a, b };
    }
    sort(p, p + n, [](const Point& l, const Point& r) {
        if(l.l == r.l) return l.r < r.r;
        return l.l < r.l;
    });
    ll l = -INF-1, r = -INF-1;
    for(int i = 0; i < n; ++i) {
        if(r < p[i].l) {
            res += r - l;
            l = p[i].l;
            r = p[i].r;
        } else {
            r = max(r, p[i].r);
        }
    }
    res += r - l;

    cout << res;

    return 0;
}
