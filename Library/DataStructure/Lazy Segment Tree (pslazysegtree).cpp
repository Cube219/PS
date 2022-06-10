struct SegTree
{
    using Type = int;

    Type merge(Type l, Type r)
    {
        return l + r;
    }

    const Type emptyNode = 0;

    vector<Type> t;
    vector<int> lazy;
    int stLeaf, n;

    SegTree(int n)
    {
        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;

        t.resize(stLeaf * 2, emptyNode);
        lazy.resize(stLeaf * 2, 0);
    }

    void initv(int idx, Type v)
    {
        t[stLeaf + idx] = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i] = merge(t[i * 2], t[i * 2 + 1]);
        }
    }

    void push(int l, int r, int node)
    {
        if(lazy[node] == 0) return;

        if(node < stLeaf) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        t[node] += (r - l + 1) * lazy[node];
        lazy[node] = 0;
    }

    Type queryImpl(int cl, int cr, int l, int r, int node)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return emptyNode;
        if(l <= cl && cr <= r) return t[node];
        int m = (cl + cr) / 2;
        return merge(queryImpl(cl, m, l, r, node * 2), queryImpl(m + 1, cr, l, r, node * 2 + 1));
    }

    void udtImpl(int cl, int cr, int l, int r, int node, Type v)
    {
        push(cl, cr, node);
        if(cr < l || r < cl) return;
        if(l <= cl && cr <= r) {
            lazy[node] += v;
            push(cl, cr, node);
            return;
        }
        int m = (cl + cr) / 2;
        udtImpl(cl, m, l, r, node * 2, v);
        udtImpl(m + 1, cr, l, r, node * 2 + 1, v);
        t[node] = merge(t[node * 2], t[node * 2 + 1]);
    }

    Type query(int l, int r)
    {
        return queryImpl(0, stLeaf - 1, l, r, 1);
    }

    void update(int l, int r, Type v)
    {
        udtImpl(0, stLeaf - 1, l, r, 1, v);
    }
};
