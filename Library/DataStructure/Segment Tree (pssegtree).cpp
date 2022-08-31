struct SegTree
{
    using T = ll;
    T merge(T l, T r)
    {
        return l + r;
    }
    const T empty = 0;

    int n;
    vector<T> t;
    SegTree(int _n) : n(_n), t(n * 2, empty) {}
    void initv(int idx, T v)
    {
        t[n + idx] = v;
    }
    void build()
    {
        for(int i = n - 1; i > 0; --i) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void update(int idx, T v)
    {
        idx += n;
        t[idx] = v;
        for(idx >>= 1; idx > 0; idx >>= 1) merge(t[idx << 1], t[idx << 1 | 1]);
    }

    T query(int l, int r)
    {
        T resl = empty, resr = empty;
        for(l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) resl = merge(resl, t[l++]);
            if(r & 1) resr = merge(t[--r], resr);
        }
        return merge(resl, resr);
    }
};
