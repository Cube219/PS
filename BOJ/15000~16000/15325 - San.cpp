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
    int h, g;
};

int n;
ll k;
Node d[41];
vector<int> hh;
vector<ll> values[50];
ll res;

int geth(int h)
{
    return lower_bound(hh.begin(), hh.end(), h) - hh.begin();
}

void bt1(int idx, int curh, ll curv)
{
    if(idx == n / 2) {
        return;
    }

    bt1(idx + 1, curh, curv);
    if(d[idx].h >= curh) {
        values[d[idx].h].push_back(curv + d[idx].g);
        bt1(idx + 1, d[idx].h, curv + d[idx].g);
    }
}

void bt2(int idx, int curh, ll curv)
{
    if(idx < n / 2) {
        for(int i = 0; i <= curh; ++i) {
            int v = lower_bound(values[i].begin(), values[i].end(), k - curv) - values[i].begin();
            res += values[i].size() - v;
        }
        return;
    }
    bt2(idx - 1, curh, curv);
    if(d[idx].h <= curh) {
        bt2(idx - 1, d[idx].h, curv + d[idx].g);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i].h >> d[i].g;
        hh.push_back(d[i].h);
    }
    hh.push_back(-1);
    sort(hh.begin(), hh.end());
    hh.erase(unique(hh.begin(), hh.end()), hh.end());
    for(int i = 0; i < n; ++i) {
        d[i].h = geth(d[i].h);
    }

    values[0].push_back(0);
    bt1(0, 0, 0);
    for(int i = 0; i < hh.size(); ++i) {
        sort(values[i].begin(), values[i].end());
    }

    bt2(n - 1, hh.size(), 0);

    cout << res;

    return 0;
}
