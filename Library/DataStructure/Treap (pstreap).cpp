struct Treap
{
    Treap* l, * r;
    int pri, sz;
    int v;

    Treap() = default;
    Treap(int _v)
    {
        l = r = nullptr;
        pri = getRandom();
        v = _v;
        sz = 1;
    }
    ~Treap()
    {
        delete l; delete r;
    }

    void update()
    {
        sz = 1;
        if(l) sz += l->sz;
        if(r) sz += r->sz;
        push();
    }

    void push()
    {
    }
};

// sz == left treap size
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

    l->push(); r->push();

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
