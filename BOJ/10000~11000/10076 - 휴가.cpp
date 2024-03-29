#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, st, steps;
vector<int> d, dd;
ll res;

struct SegTree
{
    vector<ll> t;
    vector<int> cnt;
    int st;
    void init()
    {
        st = 1;
        while(st < dd.size()) st *= 2;
        t.resize(st * 2, 0); cnt.resize(st * 2, 0);
    }

    ll queryImpl(int c, int l, int r, int node)
    {
        if(c <= 0) return 0;
        if(l == r) {
            return (ll)dd[l] * min(cnt[node], c);
        }
        int m = (l + r) / 2;

        ll res;
        if(c >= cnt[node * 2 + 1]) {
            res = t[node * 2 + 1];
        } else {
            res = queryImpl(c, m + 1, r, node * 2 + 1);
        }
        res += queryImpl(c - cnt[node * 2 + 1], l, m, node * 2);


        return res;
    }

    ll query(int cnt)
    {
        return queryImpl(cnt, 0, st - 1, 1);
    }

    void add(int v)
    {
        v += st;
        cnt[v]++;
        t[v] = (ll)dd[v - st] * cnt[v];
        for(v >>= 1; v > 0; v >>= 1) {
            t[v] = t[v * 2] + t[v * 2 + 1];
            cnt[v] = cnt[v * 2] + cnt[v * 2 + 1];
        }
    }

    void remove(int v)
    {
        v += st;
        cnt[v]--;
        t[v] = (ll)dd[v - st] * cnt[v];
        for(v >>= 1; v > 0; v >>= 1) {
            t[v] = t[v * 2] + t[v * 2 + 1];
            cnt[v] = cnt[v * 2] + cnt[v * 2 + 1];
        }
    }
};

SegTree sg;

void dnq(int s, int e, int rmin, int rmax)
{
    if(s > e) return;

    int m = (s + e) / 2;
    for(int i = m; i <= e; ++i) {
        sg.add(d[i]);
    }
    int r, rmid = rmin;
    ll mx = 0;
    for(r = rmin; r <= rmax; ++r) {
        int walk = min(r - st, st - m);
        walk += r - m;
        int remain = steps - walk;
        if(remain < 0) {
            r++;
            break;
        }
        ll v = sg.query(remain);
        if(v > mx) {
            mx = v;
            rmid = r;
        }

        if(r < rmax) sg.add(d[r + 1]);
    }
    res = max(res, mx);
    for(r = r - 1; r > rmin; --r) {
        sg.remove(d[r]);
    }

    dnq(s, m - 1, rmin, rmid);
    for(int i = m; i <= e; ++i) {
        sg.remove(d[i]);
    }
    for(int i = rmin + 1; i <= rmid; ++i) {
        sg.add(d[i]);
    }
    dnq(m + 1, e, rmid, rmax);
    for(int i = rmin + 1; i <= rmid; ++i) {
        sg.remove(d[i]);
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> st >> steps;
    d.resize(n);
    for(int& v : d) {
        cin >> v;
        dd.push_back(v);
    }
    sort(dd.begin(), dd.end());
    dd.erase(unique(dd.begin(), dd.end()), dd.end());
    for(int& v : d) {
        v = lower_bound(dd.begin(), dd.end(), v) - dd.begin();
    }

    sg.init();

    dnq(0, st, st, n - 1);

    cout << res;

    return 0;
}
