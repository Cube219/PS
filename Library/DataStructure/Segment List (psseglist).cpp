struct SegmentList
{
    struct Segment
    {
        ll l, r, v;
    };
    map<ll, Segment> list;

    SegmentList(ll mn, ll mx, ll v)
    {
        list.insert({ mn, { mn, mx, v } });
    }

    void insert(ll l, ll r, ll v)
    {
        auto stIt = prev(list.upper_bound(l));
        if(stIt->second.l < l) {
            Segment st = stIt->second;
            list.erase(stIt);

            Segment st1 = { st.l, l - 1, st.v };
            Segment st2 = { l, st.r, st.v };
            list.insert({ st1.l, st1 });
            list.insert({ st2.l, st2 });
        }
        auto edIt = prev(list.upper_bound(r));
        if(r < edIt->second.r) {
            Segment ed = edIt->second;
            list.erase(edIt);

            Segment ed1 = { ed.l, r, ed.v };
            Segment ed2 = { r + 1, ed.r, ed.v };
            list.insert({ ed1.l, ed1 });
            list.insert({ ed2.l, ed2 });
        }
        stIt = list.lower_bound(l);
        edIt = list.upper_bound(r);

        for(auto it = stIt; it != edIt; it = list.erase(it)) {
            // Do something
        }
        Segment s = { l, r, v };
        list.insert({ s.l, s });
    }
};
