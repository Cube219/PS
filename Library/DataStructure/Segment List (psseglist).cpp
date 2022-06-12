struct SegmentList
{
    struct Segment
    {
        ll l, r;
        ll v; // Data
    };

    map<ll, Segment> list;

    SegmentList(ll st, ll ed)
    {
        list.insert({ st, {st, ed, 0} });
    }

    ll query(ll l, ll r, ll v)
    {
        auto stIt = prev(list.upper_bound(l));
        if(stIt->second.l < l) {
            Segment seg = stIt->second;
            list.erase(stIt);

            Segment lSeg = seg;
            lSeg.r = l - 1;
            list.insert({ lSeg.l, lSeg });
            Segment rSeg = seg;
            rSeg.l = l;
            list.insert({ rSeg.l, rSeg }).first;
        }
        auto edIt = prev(list.upper_bound(r));
        if(r < edIt->second.r) {
            Segment seg = edIt->second;
            list.erase(edIt);

            Segment lSeg = seg;
            lSeg.r = r;
            list.insert({ lSeg.l, lSeg }).first;
            Segment rSeg = seg;
            rSeg.l = r + 1;
            list.insert({ rSeg.l, rSeg });
        }
        stIt = list.lower_bound(l);
        edIt = list.upper_bound(r);

        ll res = 0;
        for(auto it = stIt; it != edIt;) {
            Segment seg = it->second;
            // Do something

            it = list.erase(it);
        }

        Segment seg;
        seg.l = l; seg.r = r;
        // seg.v = v; // Insert new value
        list.insert({ seg.l, seg });

        return res;
    }
};
