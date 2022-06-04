#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
#include <array>
#include <chrono>
#include <random>
#include <climits>
using namespace std;

using ll = unsigned long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1LL << 32;

vector<vector<ll>> ncr(11, vector<ll>(11));
void init()
{
    for(int i = 0; i <= 10; ++i) {
        ncr[i][0] = 1;
        for(int j = 1; j <= i; ++j) {
            ncr[i][j] = ncr[i - 1][j] + ncr[i - 1][j - 1];
        }
    }
}

mt19937 rng(27);
uniform_int_distribution<int> distribution(0, INT_MAX);
int getRandom() { return distribution(rng); }

struct Treap
{
    Treap* l, * r;
    ll v;
    int pri, sz;
    array<ll, 11> ksum;

    Treap(ll _v)
    {
        l = r = nullptr;
        pri = getRandom();
        sz = 1;
        v = _v;
        for(int i = 0; i <= 10; ++i) {
            ksum[i] = v;
        }
    }
    ~Treap()
    {
        delete l; delete r;
    }

    void update()
    {
        sz = 1;
        fill(ksum.begin(), ksum.end(), v);

        if(l) {
            ksum = mvKSum(l->sz);
            for(int i = 0; i <= 10; ++i) {
                ksum[i] = (ksum[i] + l->ksum[i]) % MOD;
            }
            sz += l->sz;
        }
        if(r) {
            auto tmp = r->mvKSum(sz);
            for(int i = 0; i <= 10; ++i) {
                ksum[i] = (ksum[i] + tmp[i]) % MOD;
            }
            sz += r->sz;
        }
    }

    array<ll, 11> mvKSum(int offset)
    {
        array<ll, 11> res;
        for(int i = 0; i <= 10; ++i) {
            res[i] = 0;
            ll r = 1;
            for(int j = i; j >= 0; --j) {
                ll v = ksum[j] * r % MOD;
                v = v * ncr[i][j] % MOD;
                res[i] = (res[i] + v) % MOD;

                r = r * offset % MOD;
            }
        }

        return res;
    }
};

pair<Treap*, Treap*> split(Treap* rt, int sz)
{
    if(!rt) return{ 0, 0 };

    int lsz = rt->l ? rt->l->sz : 0;
    if(lsz + 1 <= sz) {
        auto [l, r] = split(rt->r, sz - lsz - 1);
        rt->r = l;
        rt->update();
        return { rt, r };
    } else {
        auto [l, r] = split(rt->l, sz);
        rt->l = r;
        rt->update();
        return { l, rt };
    }
}

Treap* merge(Treap* l, Treap* r)
{
    if(!l) return r; if(!r) return l;

    if(l->pri < r->pri) {
        r->l = merge(l, r->l);
        r->update();
        return r;
    } else {
        l->r = merge(l->r, r);
        l->update();
        return l;
    }
}

void solve()
{
    init();

    int n;
    cin >> n;
    Treap* tr = nullptr;
    for(int i = 0; i < n; ++i) {
        ll a;
        cin >> a;
        tr = merge(tr, new Treap(a));
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if(type == 1) {
            int pos;
            ll v;
            cin >> pos >> v;

            auto [l, r] = split(tr, pos);
            Treap* mid = new Treap(v);
            tr = merge(l, mid);
            tr = merge(tr, r);
        } else if(type == 2) {
            int pos;
            cin >> pos;

            auto [l, midr] = split(tr, pos);
            auto [mid, r] = split(midr, 1);
            delete mid;

            tr = merge(l, r);
        } else if(type == 3) {
            int pos; ll v;
            cin >> pos >> v;

            auto [l, midr] = split(tr, pos);
            auto [mid, r] = split(midr, 1);
            mid->v = v;
            fill(mid->ksum.begin(), mid->ksum.end(), v);

            tr = merge(l, mid);
            tr = merge(tr, r);
        } else {
            int l, r, k;
            cin >> l >> r >> k;

            auto [lTree, midrTree] = split(tr, l);
            auto [midTree, rTree] = split(midrTree, r - l + 1);

            cout << midTree->ksum[k] << "\n";

            tr = merge(lTree, midTree);
            tr = merge(tr, rTree);
        }
    }

    delete tr;
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
