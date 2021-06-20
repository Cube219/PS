#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;

struct Node
{
    ll n, s, e;
};

Node d[100001];
map<ll, pair<ll, ll>> mp, mp2;

ll p1(ll n, ll s, ll e)
{
    ll res = 0;
    for(ll i = s; i <= e;) {
        ll v = n / i;
        if(v == 0) break;

        ll lastidx = min(n / v, e);
        res += (lastidx - i + 1) * v;
        i = lastidx + 1;
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

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        cin >> d[i].n >> d[i].s >> d[i].e;
    }
    bool case3 = true;
    for(int i = 1; i < q; ++i) {
        if(d[i].n != d[0].n) {
            case3 = false;
            break;
        }
    }
    if(case3 == false) {
        for(int i = 0; i < q; ++i) {
            cout << p1(d[i].n, d[i].s, d[i].e) << "\n";
        }
    } else {
        ll n = d[0].n;
        ll sum = 0;
        for(ll i = 1; i <= n;) {
            ll v = n / i;
            if(v == 0) break;

            ll lastidx = min(n / v, n);
            sum += (lastidx - i + 1) * v;
            mp2.insert({ lastidx, { sum, v } });
            i = lastidx + 1;
        }

        for(int i = 0; i < q; ++i) {
            if(d[i].s > d[i].e) {
                cout << "0\n";
                continue;
            }
            ll res = 0;
            auto ed = mp2.lower_bound(d[i].e);
            if(ed == mp2.end()) {
                ed = prev(ed);
                res = ed->second.first;
            } else {
                res = ed->second.first;
                res -= (ed->first - d[i].e) * ed->second.second;
            }

            auto st = mp2.lower_bound(d[i].s);
            if(st == mp2.end()) {
                res = 0;
            } else if(st != mp2.begin()) {
                res -= st->second.first;
                res += (st->first - d[i].s + 1) * st->second.second;
            }

            cout << res << "\n";
        }
    }

    return 0;
}
