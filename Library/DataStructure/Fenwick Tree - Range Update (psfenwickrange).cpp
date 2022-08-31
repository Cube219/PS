struct FenwickRange
{
    int n;
    vector<ll> tmul, tadd;
    FenwickRange(int _n) : n(_n + 1), tmul(_n + 1, 0), tadd(_n + 1, 0) {}

    void _udt(int pos, ll mul, ll add)
    {
        for(; pos < n; pos += (pos & -pos)) {
            tmul[pos] += mul;
            tadd[pos] += add;
        }
    }

    void update(int l, int r, ll v)
    {
        l++; r++;
        _udt(l, v, -v * (l - 1));
        _udt(r, -v, v * r);
    }

    ll query(int pos)
    {
        pos++;
        ll mul = 0, add = 0;
        int st = pos;
        for(; pos > 0; pos -= (pos & -pos)) {
            mul += tmul[pos];
            add += tadd[pos];
        }
        return mul * st + add;
    }
};
