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
struct Node
{
    int x, y;
};
Node d[100001];
ll res[200001], res2[200001];
bool has[200001];

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        y--;
        d[i] = { x, y };
    }
    sort(d, d + m, [](const Node& l, const Node& r) {
        return l.x < r.x;
    });
    for(int i = 0; i < n; ++i) {
        res[i] = 1;
    }
    for(int i = 0; i < m; ++i) {
        int y = d[i].y;
        if(res[y + 1] < res[y] + 1) {
            res[y + 1] = res[y] + 1;
        }
    }
    for(int i = 0; i < m; ++i) {
        int y = d[i].y;
        if(res2[y] < res2[y + 1] + 1) {
            res2[y] = res2[y + 1] + 1;
        }
    }
    for(int i = 0; i < n; ++i) {
        cout << res[i] + res2[i] << " ";
    }

    return 0;
}
