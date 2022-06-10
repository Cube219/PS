vector<int> minFactor, mobius, primes, phi;
void initSieve(int n)
{
    minFactor.resize(n + 1, 0);
    // mobius.resize(n + 1, 0);
    // mobius[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(minFactor[i] == 0) {
            minFactor[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > n) break;
            minFactor[i * p] = p;
            // mobius[i * p] = (i % p != 0) * (-mobius[i]);
            if(i % p == 0) break;
        }
    }

    // euler phi
    /*
    phi.resize(n + 1, 0);
    iota(phi.begin(), phi.end(), 0);
    for(int i = 2; i <= n; ++i) {
        if(minFactor[i] != i) continue;
        for(int j = 1; j * i <= n; ++j) {
            phi[i * j] = (i - 1) * (phi[i * j] / i);
        }
    }
    */
}
// phi[i] = (p^a - p^(a-1))...

vector<pair<int, int>> primeFac(int v)
{
    vector<pair<int, int>> res;

    while(v > 1) {
        int f = minFactor[v];
        if(res.size() == 0 || res.back().first != f) res.emplace_back(f, 0);
        res.back().second++;
        v /= f;
    }

    return res;
}
