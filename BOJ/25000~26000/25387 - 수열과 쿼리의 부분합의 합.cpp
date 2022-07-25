#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <map>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;

struct SegmentList
{
    struct Segment
    {
        ll l, r;
        ll c;
        int qIdx;
    };

    map<ll, Segment> list;
    vector<ll> psum;

    SegmentList(ll st, ll ed)
    {
        list.insert({ st, { st, ed, 0, 0 } });
        psum.resize(ed + 1, 0);
        for(int i = 1; i <= ed; ++i) {
            psum[i] = i * (ed - i + 1);
        }
        for(int i = 1; i < ed; ++i) {
            psum[i + 1] = (psum[i + 1] + psum[i]) % MOD;
        }
    }

    ll query(ll l, ll r, ll c, int qIdx)
    {
        auto stIt = prev(list.upper_bound(l));
        if(stIt->second.l < l) {
            Segment seg = stIt->second;
            list.erase(stIt);

            Segment lSeg = seg;
            lSeg.r = l - 1;
            list.insert({ lSeg.l, lSeg });
            Segment rSeg = seg;
            rSeg.l = l;
            list.insert({ rSeg.l, rSeg }).first;
        }
        auto edIt = prev(list.upper_bound(r));
        if(r < edIt->second.r) {
            Segment seg = edIt->second;
            list.erase(edIt);

            Segment lSeg = seg;
            lSeg.r = r;
            list.insert({ lSeg.l, lSeg }).first;
            Segment rSeg = seg;
            rSeg.l = r + 1;
            list.insert({ rSeg.l, rSeg });
        }
        stIt = list.lower_bound(l);
        edIt = list.upper_bound(r);

        ll res = 0;
        for(auto it = stIt; it != edIt;) {
            Segment seg = it->second;
            res = (res + erase(seg, qIdx)) % MOD;

            it = list.erase(it);
        }

        Segment seg = { l, r, c, qIdx };
        list.insert({ seg.l, seg });

        return res;
    }

    ll erase(Segment sg, int qIdx)
    {
        ll res = (psum[sg.r] - psum[sg.l - 1] + MOD) % MOD;
        res = res * sg.c % MOD;

        ll qNum = (ll)(qIdx - sg.qIdx) * (sg.qIdx + 1) % MOD;
        res = res * qNum % MOD;

        return res;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    ll res = 0;
    SegmentList sl(1, n);
    for(int i = 0; i < q; ++i) {
        ll l, r, c;
        cin >> l >> r >> c;
        res = (res + sl.query(l, r, c, i)) % MOD;
    }

    for(auto& sg : sl.list) {
        res = (res + sl.erase(sg.second, q)) % MOD;
    }

    cout << res;
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tNum = 1;
    // cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
