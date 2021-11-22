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
    int m, k;
};

struct Node2
{
    int m;
    vector<int> k;
    ll tmp;
};

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    vector<Node> d;
    vector<int> mm;
    cin >> n;
    d.resize(n);
    for(int i = 0; i < n; ++i) {
        cin >> d[i].m >> d[i].k;
        mm.push_back(d[i].m);
    }
    sort(mm.begin(), mm.end());
    mm.erase(unique(mm.begin(), mm.end()), mm.end());
    for(int i = 0; i < n; ++i) {
        d[i].m = lower_bound(mm.begin(), mm.end(), d[i].m) - mm.begin();
    }
    sort(d.begin(), d.end(), [](const Node& l, const Node& r) {
        return l.m < r.m;
    });

    vector<Node2> d2;
    for(auto& v : d) {
        if(d2.size() == 0 || d2.back().m != v.m) {
            d2.push_back({ v.m, {}, 0 });
        }
        d2.back().k.push_back(v.k);
    }

    auto ck = [&](int num) {
        for(auto& v : d2) {
            v.tmp = 0;
            for(int k : v.k) {
                if(k >= num) v.tmp += num;
                else v.tmp += k;
            }
        }

        sort(d2.begin(), d2.end(), [](const Node2& l, const Node2& r) {
            return l.tmp > r.tmp;
        });

        ll res = 0;
        for(int i = 0; i < num; ++i) {
            res += d2[i].tmp;
        }
        return (double)res / num;
    };

    auto tsearch = [&]() {
        ll l = 1, r = d2.size();
        while(l + 2 < r) {
            ll p = (l * 2 + r) / 3;
            ll q = (l + r * 2) / 3;

            double pv = ck(p);
            double qv = ck(q);
            if(pv >= qv) r = q;
            else l = p;
        }

        double res = ck(l);
        ll rr = l;
        for(ll i = l + 1; i <= r; ++i) {
            double tmp = ck(i);
            if(res < tmp) {
                res = tmp;
                rr = i;
            }
        }
        return rr;
    };

    int res = tsearch();
    for(auto& v : d2) {
        v.tmp = 0;
        for(int k : v.k) {
            if(k >= res) v.tmp += res;
            else v.tmp += k;
        }
    }

    sort(d2.begin(), d2.end(), [](const Node2& l, const Node2& r) {
        return l.tmp > r.tmp;
    });

    cout << res << "\n";
    for(int i = 0; i < res; ++i) {
        cout << mm[d2[i].m] << " ";
    }

    return 0;
}
