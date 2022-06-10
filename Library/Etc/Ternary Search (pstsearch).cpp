auto tsearch = [](ll minx, ll maxx, const function<ll(ll)>& tfunc) {
    ll l = minx, r = maxx;
    while(l + 2 < r) {
        ll p = (l * 2 + r) / 3;
        ll q = (l + r * 2) / 3;

        ll pv = tfunc(p);
        ll qv = tfunc(q);
        
        // min
        if(pv <= qv) r = q;
        else l = p;
        // max
        if(pv <= qv) l = p;
        else r = q;
    }

    ll res = tfunc(l);
    for(ll i = l + 1; i <= r; ++i) {
        // min
        res = min(res, tfunc(i));
        // max
        res = max(res, tfunc(i));
    }
    return res;
};
