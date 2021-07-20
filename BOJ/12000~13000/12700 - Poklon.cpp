#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

struct Node
{
    int l, r;
    int par;
};

struct Value
{
    int a;
    int b2;
    bool operator<(const Value& rhs) const
    {
        Value l = *this;
        Value r = rhs;

        while(l.b2 != r.b2) {
            if(l.b2 < r.b2) {
                l.a /= 2;
                l.b2++;
            } else {
                r.a /= 2;
                r.b2++;
            }
        }
        return l.a < r.a;
    }
};

int n;
Node d[1000002];
Value res;
int maxres[1000002];

void dfs(int cur, int dep)
{
    if(d[cur].l < 0) {
        maxres[dep + 1] = max(maxres[dep + 1], -d[cur].l);
    } else {
        dfs(d[cur].l, dep + 1);
    }

    if(d[cur].r < 0) {
        maxres[dep + 1] = max(maxres[dep + 1], -d[cur].r);
    } else {
        dfs(d[cur].r, dep + 1);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        d[i].l = a;
        d[i].r = b;
        if(a > 0) d[a].par = i;
        if(b > 0) d[b].par = i;
        maxres[i] = -1;
    }

    dfs(1, 0);

    for(int i = 1; i <= n; ++i) {
        if(maxres[i] == -1) continue;
        Value v = { maxres[i], i };
        res = max(res, v);
    }

    vector<int> bit;
    while(res.a > 0) {
        bit.push_back(res.a % 2);
        res.a /= 2;
    }
    for(int i = bit.size() - 1; i >= 0; --i) {
        cout << bit[i];
    }
    for(int i = 0; i < res.b2; ++i) {
        cout << "0";
    }

    return 0;
}
