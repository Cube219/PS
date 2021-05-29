#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;
constexpr ll INF = 10000000000000000;

int n;
vector<ll> r, g, b;

ll r1(const vector<ll>& d1, const vector<ll>& d2)
{
    ll res = INF;
    for(int i = 0; i < d1.size(); ++i) {
        ll v1 = d1[i];
        auto it = lower_bound(d2.begin(), d2.end(), v1);
        if(it != d2.end()) res = min(res, abs(v1 - *it));
        if(it != d2.begin()) {
            auto it2 = prev(it);
            res = min(res, abs(v1 - *it2));
        }
        if(it != d2.end() && next(it) != d2.end()) {
            auto it2 = next(it);
            res = min(res, abs(v1 - *it2));
        }
    }
    for(int i = 0; i < d2.size(); ++i) {
        ll v1 = d2[i];
        auto it = lower_bound(d1.begin(), d1.end(), v1);
        if(it != d1.end()) res = min(res, abs(v1 - *it));
        if(it != d1.begin()) {
            auto it2 = prev(it);
            res = min(res, abs(v1 - *it2));
        }
        if(it != d1.end() && next(it) != d1.end()) {
            auto it2 = next(it);
            res = min(res, abs(v1 - *it2));
        }
    }
    return res;
}
struct Res
{
    ll v;
    int idx;
};
ll r2(const vector<ll>& d1, const vector<ll>& d2, const vector<ll>& p)
{
    vector<Res> d1res, d2res;
    for(int i = 0; i < d1.size(); ++i) {
        ll v1 = d1[i];
        auto it = lower_bound(p.begin(), p.end(), v1);
        int idx = it - p.begin();
        if(it != p.end()) d1res.push_back({ abs(v1 - *it), idx });
        if(it != p.begin()) {
            auto it2 = prev(it);
            d1res.push_back({ abs(v1 - *it2), idx - 1 });
        }
        if(it != p.end() && next(it) != p.end()) {
            auto it2 = next(it);
            d1res.push_back({ abs(v1 - *it2), idx + 1 });
        }
    }
    for(int i = 0; i < d2.size(); ++i) {
        ll v1 = d2[i];
        auto it = lower_bound(p.begin(), p.end(), v1);
        int idx = it - p.begin();
        if(it != p.end()) d2res.push_back({ abs(v1 - *it), idx });
        if(it != p.begin()) {
            auto it2 = prev(it);
            d2res.push_back({ abs(v1 - *it2), idx - 1 });
        }
        if(it != p.end() && next(it) != p.end()) {
            auto it2 = next(it);
            d2res.push_back({ abs(v1 - *it2), idx + 1 });
        }
    }
    sort(d1res.begin(), d1res.end(), [](const Res& l, const Res& r) {
        return l.v < r.v;
    });
    sort(d2res.begin(), d2res.end(), [](const Res& l, const Res& r) {
        return l.v < r.v;
    });
    ll res = INF;
    for(int i = 0; i < 2 && i < d1res.size(); ++i) {
        for(int j = 0; j < 2 && j < d2res.size(); ++j) {
            if(d1res[i].idx == d2res[j].idx) continue;
            res = min(res, d1res[i].v + d2res[i].v);
        }
    }
    return res;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n * 2; ++i) {
        ll a;
        char ch;
        cin >> a >> ch;
        if(ch == 'R') r.push_back(a);
        else if(ch == 'G') g.push_back(a);
        else b.push_back(a);
    }
    if(r.size() % 2 == 0 && g.size() % 2 == 0 && b.size() % 2 == 0) {
        cout << "0";
        return 0;
    }

    sort(r.begin(), r.end());
    sort(g.begin(), g.end());
    sort(b.begin(), b.end());

    ll res = INF;
    if(r.size() % 2 == 0) {
        res = min(res, r1(g, b));
        res = min(res, r2(g, b, r));
    } else if(g.size() % 2 == 0) {
        res = min(res, r1(r, b));
        res = min(res, r2(r, b, g));
    } else {
        res = min(res, r1(r, g));
        res = min(res, r2(r, g, b));
    }

    cout << res;

    return 0;
}
