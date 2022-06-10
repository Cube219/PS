struct DSU
{
    int n;
    vector<int> par, sz;
    DSU(int _n) : n(_n), par(_n)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        while(x != par[x]) x = par[x] = par[par[x]];
        return x;
    }

    bool uni(int a, int b)
    {
        a = find(a);
        b = find(b);
        if(a == b) return false;
        par[b] = a;
        return true;
    }
};
