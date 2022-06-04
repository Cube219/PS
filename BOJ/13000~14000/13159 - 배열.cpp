#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>
#include <climits>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

mt19937 rng(27);
uniform_int_distribution<int> distribution(0, INT_MAX);
int getRandom() { return distribution(rng); }

struct Treap
{
    Treap* l, * r, *par;
    int pri, key, v;
    int sz, mn, mx;
    ll sum;
    bool isFlip;

    Treap() = default;
    Treap(int _key, int _v)
    {
        l = r = par = nullptr;
        pri = getRandom();
        key = _key;
        v = mn = mx = sum = _v;
        sz = 1;
        isFlip = false;
    }
    ~Treap()
    {
        delete l; delete r;
    }

    void update()
    {
        sz = 1;
        mn = mx = sum = v;
        if(l) {
            sz += l->sz;
            mn = min(mn, l->mn);
            mx = max(mx, l->mx);
            sum += l->sum;
            l->par = this;
        }
        if(r) {
            sz += r->sz;
            mn = min(mn, r->mn);
            mx = max(mx, r->mx);
            sum += r->sum;
            r->par = this;
        }
        push();
    }

    void push()
    {
        if(!isFlip) return;

        if(l) l->isFlip = !l->isFlip;
        if(r) r->isFlip = !r->isFlip;
        swap(l, r);
        isFlip = false;
    }
};

pair<Treap*, Treap*> split(Treap* rt, int sz)
{
    if(!rt) return { 0, 0 };

    rt->push();
    rt->par = nullptr;

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

    l->push(); r->push();
    l->par = nullptr;
    r->par = nullptr;

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

Treap* insert(Treap* rt, Treap* node)
{
    if(!rt) return node;

    if(node->pri > rt->pri) {
        auto [l, r] = split(rt, node->key);
        node->l = l; node->r = r;
        node->update();
        return node;
    }
    if(node->key < rt->key) {
        rt->l = insert(rt->l, node);
    }
    else {
        rt->r = insert(rt->r, node);
    }
    rt->update();
    return rt;
}

Treap* erase(Treap* rt, int key)
{
    if(!rt) return rt;

    if(rt->key == key) {
        auto tmp = merge(rt->l, rt->r);
        delete rt;
        return tmp;
    }
    if(key < rt->key) rt->l = erase(rt->l, key);
    else rt->r = erase(rt->r, key);
    rt->update();
    return rt;
}

void solve()
{
    int n, q;
    cin >> n >> q;

    Treap* tree = nullptr;
    vector<Treap*> nodes(n);
    for(int i = 0; i < n; ++i) {
        nodes[i] = new Treap(i, i + 1);
        tree = insert(tree, nodes[i]);
    }

    for(int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if(type == 1) {
            int l, r;
            cin >> l >> r;
            l--; r--;

            auto [tl, tmp] = split(tree, l);
            auto [t, tr] = split(tmp, r  - l + 1);

            cout << t->mn << " " << t->mx << " " << t->sum << "\n";
            t->isFlip = !t->isFlip;

            tree = merge(tl, t);
            tree = merge(tree, tr);
        } else if(type == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            l--; r--; x = -x;
            x = x % (r - l + 1);

            auto [tl, tmp] = split(tree, l);
            auto [t, tr] = split(tmp, r - l + 1);

            cout << t->mn << " " << t->mx << " " << t->sum << "\n";
            if(x < 0) {
                x = t->sz + x;
            }
            if(x > 0) {
                auto [tmp1, tmp2] = split(t, x);
                t = merge(tmp2, tmp1);
            }

            tree = merge(tl, t);
            tree = merge(tree, tr);
        } else if(type == 3) {
            int pos;
            cin >> pos;
            pos--;

            auto kth = [](auto&& self, Treap* rt, int k) -> int {
                rt->push();
                int lsz = rt->l ? rt->l->sz : 0;
                if(lsz == k) return rt->v;
                else if(lsz > k) return self(self, rt->l, k);
                else return self(self, rt->r, k - lsz - 1);
            };
            cout << kth(kth, tree, pos) << "\n";
        } else {
            int x;
            cin >> x;

            Treap* cur = nodes[x - 1];
            vector<char> isRight;
            while(cur->par != nullptr) {
                if(cur == cur->par->l) isRight.push_back(false);
                else isRight.push_back(true);
                cur = cur->par;
            }

            int res = 0;
            cur = tree;
            while(isRight.size() > 0) {
                bool f = isRight.back(); isRight.pop_back();
                if(cur->isFlip) f = !f;

                cur->push();
                cur->update();
                if(f) {
                    res++;
                    if(cur->l) res += cur->l->sz;
                    cur = cur->r;
                } else cur = cur->l;
            }

            cur->push();
            if(cur->l) res += cur->l->sz;
            cout << res + 1 << "\n";
        }
    }

    auto dfs = [](auto&& self, Treap* cur) -> void {
        cur->push();
        if(cur->l) self(self, cur->l);
        cout << cur->v << " ";
        if(cur->r) self(self, cur->r);
    };
    dfs(dfs, tree);

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
