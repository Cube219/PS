#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Square
{
    ll x, y, w, h;
};
struct Node
{
    ll x;
    ll y1, y2;
    int idx;
};

int n;
int par[50001];
ll res[50001];
Square s[50001];
Node d[200001];
ll maxres;

vector<int> st;
int find(int v)
{
    while(par[v] != v) {
        st.push_back(v);
        v = par[v];
    }
    for(int t : st) {
        par[t] = v;
    }
    st.clear();
    return v;
}

void uni(int a, int b)
{
    int ap = find(a);
    int bp = find(b);
    if(ap == bp) return;
    res[bp] += res[ap];
    maxres = max(maxres, res[bp]);
    par[ap] = bp;
}


vector<Node> tmp;
void p2()
{
    int curidx = tmp[0].idx;
    ll r = tmp[0].y2;
    for(int j = 1; j < tmp.size(); ++j) {
        if(r < tmp[j].y1) {
            curidx = tmp[j].idx;
            r = tmp[j].y2;
        } else {
            r = max(r, tmp[j].y2);
            uni(curidx, tmp[j].idx);
        }
    }
}
void process()
{
    sort(d, d + n * 2, [](const Node& l, const Node& r) {
        if(l.x == r.x) return l.y1 < r.y1;
        return l.x < r.x;
    });

    ll lastx = d[0].x;
    tmp.clear();
    for(int i = 0; i < n * 2; ++i) {
        if(lastx == d[i].x) {
            tmp.push_back(d[i]);
        } else {
            p2();

            lastx = d[i].x;
            tmp.clear();
            tmp.push_back(d[i]);
        }
    }
    if(tmp.size() > 0) p2();
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
        ll x, y, w, h;
        cin >> x >> y >> w >> h;
        s[i] = { x, y, w, h };
        d[i * 2] = { x, y, y + h, i };
        d[i * 2 + 1] = { x + w, y, y + h, i };
        par[i] = i;
        res[i] = w * h;
        maxres = max(maxres, res[i]);
    }
    process();
    for(int i = 0; i < n; ++i) {
        ll x = s[i].x;
        ll y = s[i].y;
        ll w = s[i].w;
        ll h = s[i].h;

        d[i * 2] = { y, x, x + w, i };
        d[i * 2 + 1] = { y + h, x, x + w, i };
    }
    process();

    cout << maxres;

    return 0;
}
