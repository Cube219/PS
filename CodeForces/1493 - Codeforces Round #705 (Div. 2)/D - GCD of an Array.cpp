#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;

int tNum;
int n, qNum;
map<int, int> pp[20001];
constexpr ll MOD = 1000000007;

constexpr int MAXN = 200001;
int min_factor[MAXN + 1];
vector<int> primes;
int primeIdx[200001];
vector<pair<int, int>> fPrimes;

void init_primes()
{
    for(int i = 2; i <= MAXN; i++) {
        min_factor[i] = i;
    }

    for(int i = 2; i * i <= MAXN; i++) {
        if(min_factor[i] == i) {
            for(int j = i * i; j <= MAXN; j += i) {
                if(min_factor[j] == j) {
                    min_factor[j] = i;
                }
            }
        }
    }

    for(int i = 2; i <= MAXN; ++i) {
        if(min_factor[i] == i) {
            primes.push_back(i);
            primeIdx[i] = primes.size() - 1;
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

ll refresh(int v)
{
    ll num = 99999999;
    for(auto& node : pp[v]) {
        num = min(num, (ll)node.second);
    }
    vector<int> tmp;
    for(auto& node : pp[v]) {
        node.second -= num;
        if(node.second == 0) {
            tmp.push_back(node.first);
        }
    }

    for(int idx : tmp) {
        pp[v].erase(idx);
    }

    return num;
}

ll mypow(ll a, ll b)
{
    ll res = 1;
    for(int i = 0; i < b; ++i) {
        res = (res * a) % MOD;
    }
    return res;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes();

    cin >> n >> qNum;
    for(int i = 0; i < n; ++i) {
        int d;
        cin >> d;

        get_f_primes(d);

        for(int j = 0; j < fPrimes.size(); ++j) {
            int p = fPrimes[j].first;
            int pIdx = primeIdx[p];
            int cnt = fPrimes[j].second;

            pp[pIdx].insert({ i + 1, cnt });
        }
    }

    ll res = 1;
    for(int i = 0; i < primes.size(); ++i) {
        if(pp[i].size() == n) {
            ll t = refresh(i);
            t = mypow(primes[i], t);
            res = (res * t) % MOD;
        }
    }

    for(int i = 0; i < qNum; ++i) {
        int idx, v;
        cin >> idx >> v;

        get_f_primes(v);

        for(int j = 0; j < fPrimes.size(); ++j) {
            int p = fPrimes[j].first;
            int pIdx = primeIdx[p];
            int cnt = fPrimes[j].second;

            auto findIt = pp[pIdx].find(idx);
            if(findIt != pp[pIdx].end()) {
                cnt += findIt->second;
                pp[pIdx].erase(findIt);
            }
            pp[pIdx].insert({ idx, cnt });

            if(pp[pIdx].size() == n) {
                ll num = refresh(pIdx);
                ll tmp = mypow(p, num);
                res = (res * tmp) % MOD;
            }
        }

        cout << res << "\n";
    }

    return 0;
}
