#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXN = 100001;
int min_factor[MAXN + 1];
vector<int> primes;
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        if(min_factor[i] == 0) {
            min_factor[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > MAXN) break;
            min_factor[i * p] = p;
            if(i % p == 0) break;
        }
    }
}

void get_f_primes(int v)
{
    fPrimes.clear();

    while(v > 1) {
        int f = min_factor[v];
        if(fPrimes.size() == 0 || fPrimes.back().first != f) {
            fPrimes.push_back(make_pair(f, 0));
        }
        fPrimes.back().second++;
        v /= f;
    }
}

int k;
vector<int> g[200001];
int d[200001];

void bt(int cur, int v, int idx, vector<int>& dl)
{
    if(idx == fPrimes.size()) {
        dl.push_back(v);
        return;
    }

    int vv = 1;
    bt(cur, v, idx + 1, dl);
    for(int i = 0; i < fPrimes[idx].second; ++i) {
        vv *= fPrimes[idx].first;
        bt(cur, v * vv, idx + 1, dl);
    }
}

int p(int cur)
{
    if(d[cur] != -1) return d[cur];

    vector<int> g;
    get_f_primes(cur);
    vector<int> dl;
    bt(cur, 1, 0, dl);
    for(int i = 0; i < dl.size(); ++i) {
        if(cur + dl[i] > k) continue;
        g.push_back(p(cur + dl[i]));
    }
    sort(g.begin(), g.end());
    g.erase(unique(g.begin(), g.end()), g.end());
    d[cur] = 0;
    for(int i = 0; i < g.size(); ++i) {
        if(g[i] != i) break;
        d[cur]++;
    }
    return d[cur];
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes();

    cin >> k;
    for(int i = 1; i <= k; ++i) {
        d[i] = -1;
    }
    p(1);
    if(d[1] > 0) cout << "Kali";
    else cout << "Ringo";

    return 0;
}
