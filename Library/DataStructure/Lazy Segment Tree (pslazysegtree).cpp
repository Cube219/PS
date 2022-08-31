struct SegTree
{
    using T = int;
    T merge(T l, T r)
    {
        return l + r;
    }
    const T emptyNode = 0;

    vector<T> t;
    vector<int> lazy;
    int n;

    SegTree(int _n)
    {
        n = 1;
        while(n < _n) n <<= 1;

        t.resize(n << 1, emptyNode);
        lazy.resize(n << 1, 0);
    }

    void initv(int idx, T v)
    {
        t[n + idx] = v;
    }

    void build()
    {
        for(int i = n - 1; i > 0; --i) t[i] = merge(t[i << 1], t[i << 1 | 1]);
    }

    void push(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < n) {
            lazy[node << 1] += lazy[node];
            lazy[node << 1 | 1] += lazy[node];
        }
        t[node] += (r - l + 1) * lazy[node];
        lazy[node] = 0;
    }

    T _qry(int cl, int cr, int l, int r, int node)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return emptyNode;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) >> 1;
        return merge(_qry(cl, m, l, r, node << 1), _qry(m + 1, cr, l, r, node << 1 | 1));
    }

    void _udt(int cl, int cr, int l, int r, int node, T v)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            push(cl, cr, node);
            return;
        }
        int m = (cl + cr) >> 1;
        _udt(cl, m, l, r, node << 1, v);
        _udt(m + 1, cr, l, r, node << 1 | 1, v);
        t[node] = merge(t[node << 1], t[node << 1 | 1]);
    }

    T query(int l, int r)
    {
        return _qry(0, n - 1, l, r, 1);
    }

    void update(int l, int r, T v)
    {
        _udt(0, n - 1, l, r, 1, v);
    }
};
