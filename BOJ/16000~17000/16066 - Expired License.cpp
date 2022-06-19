#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

using ll = long long int;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LNF = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1'000'000'007;

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

void solve()
{
    string a, b;
    cin >> a >> b;

    auto p = [](string& s) {
        ll res = 0;
        int dNum = -1;
        for(char ch : s) {
            if(ch == '.') {
                dNum = 0;
            } else {
                res *= 10;
                res += ch - '0';
                if(dNum >= 0) dNum++;
            }
        }
        for(int i = 0; i < 5 - dNum; ++i) {
            res *= 10;
        }

        return res;
    };
    ll aa = p(a), bb = p(b);
    
    auto g = gcd(aa, bb);
    aa /= g; bb /= g;
    if(aa == 1 && bb == 1) {
        aa = bb = 2;
    }

    if(minFactor[aa] != aa || minFactor[bb] != bb) {
        cout << "impossible\n";
    } else {
        cout << aa << " " << bb << "\n";
    }
}

int main()
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    initSieve(10000005);

    int tNum = 1;
    cin >> tNum;
    for(int tt = 1; tt <= tNum; tt++) {
        solve();
    }

    return 0;
}
