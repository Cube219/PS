#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

using ll = long long int;

struct Node
{
    double x, y;
};

struct Edge
{
    int u, v;
    double dis;
};

int w, h;
int n;
Node d[1001];
vector<Edge> e;
int par[1020];
int ld, rd, ud, dd;

int find(int v)
{
    vector<int> st;
    while(par[v] != v) {
        st.push_back(v);
        v = par[v];
    }
    for(int i = 0; i < st.size(); ++i) {
        par[st[i]] = v;
    }
    return v;
}
void uni(int a, int b)
{
    int ar = find(a);
    int br = find(b);
    if(ar == br) return;

    par[br] = ar;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> w >> h >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].x >> d[i].y;
    }
    ld = n;
    rd = n + 1;
    ud = n + 2;
    dd = n + 3;
    for(int i = 0; i < n + 4; ++i) {
        par[i] = i;
    }

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            double dx = d[i].x - d[j].x;
            double dy = d[i].y - d[j].y;
            double dis = sqrt(dx * dx + dy * dy) / 2.0;
            e.push_back({ i, j, dis });
        }
        e.push_back({ i, ld, d[i].x });
        e.push_back({ i, rd, w - d[i].x });
        e.push_back({ i, ud, h - d[i].y });
        e.push_back({ i, dd, d[i].y });
    }
    sort(e.begin(), e.end(), [](const Edge& l, const Edge& r) {
        return l.dis < r.dis;
    });
    double res = 0.0;
    for(int i = 0; i < e.size(); ++i) {
        uni(e[i].u, e[i].v);
        int lr = find(ld);
        int rr = find(rd);
        int ur = find(ud);
        int dr = find(dd);

        if(lr == rr || ur == dr || ur == rr || lr == dr) {
            res = e[i].dis;
            break;
        }
    }

    cout << fixed << setprecision(8) << res;

    return 0;
}
