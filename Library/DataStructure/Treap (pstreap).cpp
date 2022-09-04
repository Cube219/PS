struct Treap
{
    Treap* l, * r;
    int pri, sz;
    ll v;

    Treap(ll _v) : l(0), r(0), pri(getRandom()), sz(1), v(_v) {}
    ~Treap() { delete l; delete r; }

    void update()
    {
        sz = 1;
        if(l) sz += l->sz;
        if(r) sz += r->sz;
        push();
    }

    void push() {}
};

// sz -> left tree size
pair<Treap*, Treap*> split(Treap* cur, int sz)
{
    if(!cur) return { 0, 0 };
    cur->push();

    int lsz = cur->l ? cur->l->sz : 0;
    if(lsz + 1 <= sz) {
        auto [l, r] = split(cur->r, sz - lsz - 1);
        cur->r = l; cur->update();
        return { cur, r };
    } else {
        auto [l, r] = split(cur->l, sz);
        cur->l = r; cur->update();
        return { l, cur };
    }
}

Treap* merge(Treap* l, Treap* r)
{
    if(!l) return r; if(!r) return l;
    l->push(); r->push();

    if(l->pri > r->pri) {
        l->r = merge(l->r, r);
        l->update();
        return l;
    } else {
        r->l = merge(l, r->l);
        r->update();
        return r;
    }
}
