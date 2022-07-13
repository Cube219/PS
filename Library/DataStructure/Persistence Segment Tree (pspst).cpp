struct PST
{
    using Type = ll;

    Type merge(Type l, Type r)
    {
        return l + r;
    }

    const Type empty = 0;

    struct Node
    {
        int l = -1, r = -1;
        Type v = empty;
    };

    vector<Node> t;
    int stLeaf;
    vector<int> root;

    PST(int n)
    {
        root.push_back(1);

        stLeaf = 1;
        while(stLeaf < n) stLeaf *= 2;
        t.resize(stLeaf * 2);
    }

    void initv(int idx, Type v)
    {
        t[stLeaf + idx].v = v;
    }

    void build()
    {
        for(int i = stLeaf - 1; i > 0; --i) {
            t[i].v = merge(t[i * 2].v, t[i * 2 + 1].v);
            t[i].l = i * 2;
            t[i].r = i * 2 + 1;
        }
    }

    Type queryImpl(int cl, int cr, int l, int r, int node)
    {
        if(l <= cl && cr <= r) return t[node].v;
        else if(cr < l || r < cl) return empty;
        int m = (cl + cr) / 2;
        return merge(queryImpl(cl, m, l, r, t[node].l), queryImpl(m + 1, cr, l, r, t[node].r));
    }

    Type query(int l, int r, int version)
    {
        return queryImpl(0, stLeaf - 1, l, r, root[version]);
    }

    void update(int idx, Type v)
    {
        int cl = 0, cr = stLeaf - 1;
        int node = root.back();

        int newnode = t.size();
        root.push_back(newnode);
        t.push_back(t[node]);

        while(cl != cr) {
            int m = (cl + cr) / 2;
            if(idx <= m) {
                cr = m;
                t[newnode].l = newnode + 1;
                newnode++;

                node = t[node].l;
                t.push_back(t[node]);
            } else {
                cl = m + 1;
                t[newnode].r = newnode + 1;
                newnode++;

                node = t[node].r;
                t.push_back(t[node]);
            }
        }
        t[newnode].v = v;
        newnode--;
        while(newnode >= root.back()) {
            t[newnode].v = merge(t[t[newnode].l].v, t[t[newnode].r].v);
            newnode--;
        }
    }

    void remove(int numrt)
    {
        int rmrt = root[root.size() - numrt];
        t.erase(t.begin() + rmrt, t.end());
        root.erase(root.end() - numrt, root.end());
    }
};
