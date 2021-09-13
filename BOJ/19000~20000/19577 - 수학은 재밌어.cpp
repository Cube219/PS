#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

constexpr int MAXN = 70000;
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
// ep[i] = f^a(1 - 1/f)...

int ep[MAXN + 1];

void init()
{
    init_primes();

    for(int i = 1; i <= MAXN; ++i) {
        ep[i] = 1;
        get_f_primes(i);
        for(auto f : fPrimes) {
            int v = 1;
            for(int j = 0; j < f.second; ++j) {
                v *= f.first;
            }
            ep[i] *= v - v / f.first;
        }
    }
}

int tNum;
ll n;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init();

    cin >> n;
    for(int i = 1; i <= MAXN; ++i) {
        ll v = (ll)i * ep[i];
        if(v == n) {
            cout << i;
            return 0;
        }
        // if(i >= 70000 && v <= 1000000000) {
        //     cout << i << " " << v << "\n";
        // }
    }
    cout << "-1";

    return 0;
}
