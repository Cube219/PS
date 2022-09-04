struct SegTree
{
    using T = ll;
    T merge(T l, T r)
    {
        return l + r;
    }
    constexpr static T empty = 0;

    int n;
    vector<T> t;
    SegTree(int _n) : n(_n), t(_n * 2, empty) {}
    void initv(int idx, T v)
    {
        t[n + idx] = v;
    }
    void build()
    {
        for(int i = n - 1; i > 0; --i) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void update(int pos, T v)
    {
        pos += n;
        t[pos] = v;
        for(pos >>= 1; pos > 0; pos >>= 1) t[pos] = merge(t[pos << 1], t[pos << 1 | 1]);
    }

    T query(int l, int r)
    {
        T lres = empty, rres = empty;
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) lres = merge(lres, t[l++]);
            if(r & 1) rres = merge(t[--r], rres);
        }
        return merge(lres, rres);
    }
};
