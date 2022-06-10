vector<pair<ll, int>> largePrimeFac(ll v)
{
    vector<pair<ll, int>> res;
    ll sqv = sqrtl(v);

    for(ll f = 2; f <= sqv && v > 1; ++f) {
        if(v % f != 0) continue;
        res.emplace_back(f, 0);
        while(v % f == 0) {
            res.back().second++;
            v /= f;
        }
    }
    if(v > 1) res.emplace_back(v, 1);

    return res;
}
