#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <vector>
#include <climits>
#include <random>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution(0, INT_MAX);
int getRandom() { return distribution(rng); }

struct Treap
{
    Treap* l, * r;
    int pri, sz, v;
    int lmx, rmx, mx;
    bool isFlip;

    Treap(int _v)
    {
        l = r = nullptr;
        pri = getRandom();
        sz = 1;
        v = _v;
        isFlip = false;

        if(v == 0) lmx = rmx = mx = 0;
        else lmx = rmx = mx = 1;
    }
    ~Treap()
    {
        delete l; delete r;
    }

    void update()
    {
        push();
        if(l) l->push();
        if(r) r->push();

        mx = lmx = rmx = 0;

        // mx
        if(l) mx = max(mx, l->mx);
        if(r) mx = max(mx, r->mx);
        if(v == 1) {
            int tmp = 1;
            if(l) tmp += l->rmx;
            if(r) tmp += r->lmx;
            mx = max(mx, tmp);
        }

        // lmx
        if(l) lmx = l->lmx;
        if(v == 1 && (!l || lmx == l->sz)) {
            lmx++;
            if(r) lmx += r->lmx;
        }

        // rmx
        if(r) rmx = r->rmx;
        if(v == 1 && (!r || rmx == r->sz)) {
            rmx++;
            if(l) rmx += l->rmx;
        }

        // sz
        sz = 1;
        if(l) sz += l->sz;
        if(r) sz += r->sz;
    }

    void push()
    {
        if(!isFlip) return;
        if(l) l->isFlip = !l->isFlip;
        if(r) r->isFlip = !r->isFlip;

        swap(l, r);
        swap(lmx, rmx);
        isFlip = false;
    }
};

pair<Treap*, Treap*> split(Treap* rt, int sz)
{
    if(!rt) return { 0, 0 };

    rt->push();

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

    l->push();
    r->push();

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
    int n;
    cin >> n;
    Treap* tree = nullptr;
    for(int i = 0; i < n; ++i) {
        int a; cin >> a;
        tree = merge(tree, new Treap(a));
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int type, l, r;
        cin >> type >> l >> r;
        l--; r--;
        auto [lTree, midrTree] = split(tree, l);
        auto [midTree, rTree] = split(midrTree, r - l + 1);

        if(type == 1) {
            midTree->isFlip = !midTree->isFlip;
        } else {
            cout << midTree->mx << "\n";
        }

        tree = merge(lTree, midTree);
        tree = merge(tree, rTree);
    }

    delete tree;
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
