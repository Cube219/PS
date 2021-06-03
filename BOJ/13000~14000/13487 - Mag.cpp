#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 1000000001;

int n;
vector<int> g[1000001];
int d[1000001], minv = INF;
double res;
int ru, rd;

struct RetNode
{
    int onenum = 0;
    int twonum = 0;
};

RetNode dfs(int cur, int par)
{
    int one1 = 0, one2 = 0;
    int one1node = -1, one2node = -1, twonode = -1;
    int two = 0;
    for(int nxt : g[cur]) {
        if(nxt == par) continue;

        RetNode r = dfs(nxt, cur);
        if(one2 < r.onenum) {
            one2 = r.onenum;
            one2node = nxt;
        }
        if(one1 < one2) {
            swap(one1, one2);
            swap(one1node, one2node);
        }
        if(two < r.twonum) {
            two = r.twonum;
            twonode = nxt;
        }
    }

    RetNode ret;
    if(d[cur] == 1) {
        int num = one1 + one2 + 1;
        double v = 1.0 / num;
        if(res > v) {
            res = v;
            ru = 1;
            rd = num;
        }

        if(one1node == twonode) {
            swap(one1, one2);
        }
        num = two + one1 + 1;
        v = 2.0 / num;
        if(res > v) {
            res = v;
            ru = 2;
            rd = num;
        }

        ret.onenum = max(one1, one2) + 1;
        if(two > 0) {
            ret.twonum = two + 1;
        }
    } else if(d[cur] == 2) {
        int num = one1 + one2 + 1;
        double v = 2.0 / num;
        if(res > v) {
            res = v;
            ru = 2;
            rd = num;
        }
        ret.twonum = one1 + 1;
    }
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        minv = min(minv, d[i]);
    }
    res = minv;
    ru = minv;
    rd = 1;

    dfs(0, -1);

    if(ru == 2 && rd % 2 == 0) {
        ru = 1;
        rd /= 2;
    }
    cout << ru << "/" << rd;

    return 0;
}
