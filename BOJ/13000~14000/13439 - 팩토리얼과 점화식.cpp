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
int n, k;

constexpr int MAXN = 1000;
int min_factor[MAXN + 1];
vector<pair<int, int>> fPrimes;
ll fNum[1001];
map<ll, ll> pNum;
map<ll, ll> cpNum;
ll t[1001][2];

constexpr ll MOD = 1000000009;

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


int main(void)
{
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    init_primes();

    cin >> n >> k;
    t[k][0] = 1;
    t[k][1] = 1;
    fNum[n] = 1;

    for(int i = n - 1; i >= 1; --i) {
        ll sum = 0;
        int cur = i % 2;
        int prev = 1 - cur;

        for(int j = k; j >= 2; --j) {
            t[j][cur] = (t[j][prev] + t[j + 1][cur]) % MOD;
            sum = (sum + t[j][cur]) % MOD;
        }
        fNum[i] = sum;
    }

    for(int i = 2; i <= n; ++i) {
        get_f_primes(i);

        for(int j = 0; j < fPrimes.size(); ++j) {
            auto findIt = cpNum.find(fPrimes[j].first);
            if(findIt == cpNum.end()) {
                cpNum.insert({ fPrimes[j].first, fPrimes[j].second });
            } else {
                findIt->second += fPrimes[j].second;
            }
        }

        for(auto& node : cpNum) {
            auto findIt = pNum.find(node.first);
            if(findIt == pNum.end()) {
                pNum.insert({ node.first, (node.second * fNum[i]) % MOD });
            } else {
                findIt->second = (((node.second * fNum[i]) % MOD) + findIt->second) % MOD;
            }
        }
    }

    ll res = 1;
    for(auto& node : pNum) {
        res = ((node.second + 1) * res) % MOD;
    }

    cout << res;

    return 0;
}
