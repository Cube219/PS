#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 999999999999999;

struct Node
{
    int price;
    int value;
};

int n;
Node d[32];
ll k;
int m, h[32];
vector<pair<ll, ll>> mp;
vector<ll> values;
vector<ll> minprice;
ll res = INF;

void bt(int idx, ll p, ll v)
{
    if(idx == n / 2) {
        mp.push_back({ v, p });
        return;
    }
    bt(idx + 1, p, v);
    bt(idx + 1, p + d[idx].price, v + d[idx].value);
}

void bt2(int idx, ll p, ll v)
{
    if(idx == n) {
        ll remain = k - v;
        int idx = lower_bound(values.begin(), values.end(), remain) - values.begin();
        if(idx < values.size()) {
            res = min(res, minprice[idx] + p);
        }
        return;
    }
    bt2(idx + 1, p, v);
    bt2(idx + 1, p + d[idx].price, v + d[idx].value);
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
        cin >> d[i].price;
    }
    for(int i = 0; i < n; ++i) {
        cin >> d[i].value;
    }
    cin >> k;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        cin >> h[i];
    }
    bt(0, 0, 0);

    sort(mp.begin(), mp.end(), [](const auto& l, const auto& r) {
        return l.first < r.first;
    });
    minprice.resize(mp.size());
    minprice.back() = mp.back().second;
    for(int i = mp.size() - 2; i >= 0; --i) {
        minprice[i] = min(minprice[i + 1], mp[i].second);
    }
    values.resize(mp.size());
    for(int i = 0; i < mp.size(); ++i) {
        values[i] = mp[i].first;
    }

    bt2(n / 2, 0, 0);

    if(res == INF) res = -1;
    else {
        for(int i = 0; i < m; ++i) {
            res -= d[h[i]].price;
        }
        if(res < 0) res = 0;
    }

    cout << res;

    return 0;
}
