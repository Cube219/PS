#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <map>

using namespace std;

#ifdef CUBE_PS
#include <unordered_map>
#include <unordered_set>
template <typename K, typename V>
using hash_map = unordered_map<K, V>;

template <typename K>
using hash_set = unordered_set<K>;
#else
#include <bits/extc++.h> /** keep-include */

struct splitmix64_hash
{
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        return splitmix64(x + 0x2425260000242526);
    }
};

template <typename K, typename V>
using hash_map = __gnu_pbds::gp_hash_table<K, V, splitmix64_hash>;

template <typename K>
using hash_set = hash_map<K, __gnu_pbds::null_type>;
#endif


using ll = long long int;
constexpr ll h = 3137;
constexpr ll MOD = 998244353;
constexpr ll h2 = 53;
constexpr ll MOD2 = 1610612741;

struct StrHash
{
    vector<ll> hv;
    vector<ll> hpow;
    vector<ll> hv2;
    vector<ll> hpow2;

    void build(const string& str)
    {
        int n = str.size();
        hv.resize(n);
        hpow.resize(n);
        hv2.resize(n);
        hpow2.resize(n);

        hv[0] = str[0];
        hpow[0] = 1;
        hv2[0] = str[0];
        hpow2[0] = 1;
        for(int i = 1; i < n; ++i) {
            hv[i] = (hv[i - 1] * h + str[i]) % MOD;
            hpow[i] = (hpow[i - 1] * h) % MOD;
            hv2[i] = (hv2[i - 1] * h2 + str[i]) % MOD2;
            hpow2[i] = (hpow2[i - 1] * h2) % MOD2;
        }
    }

    // [l, r]
    ll substr(int l, int r)
    {
        ll res = hv[r];
        if(l > 0) {
            res -= hv[l - 1] * hpow[r - l + 1];
            res = ((res % MOD) + MOD) % MOD;
        }
        ll res2 = hv2[r];
        if(l > 0) {
            res2 -= hv2[l - 1] * hpow2[r - l + 1];
            res2 = ((res2 % MOD2) + MOD2) % MOD2;
        }
        return (res << 32) | (res2);
    }
};

StrHash sh;
int n;
string str;
ll res[200007];
hash_map<ll, int> bucket;

void p1(int k)
{
    bucket.clear();
    for(int i = 0; i + k - 1 < n; i += k) {
        ll hash = sh.substr(i, i + k - 1);

        ll curh = 1;
        ll curh2 = 1;
        for(int j = k - 1; j >= 0; --j) {
            ll hashl = hash >> 32;
            hashl = ((hashl - curh * str[i + j]) % MOD + MOD) % MOD;
            hashl = (hashl + curh * '?') % MOD;
            ll hashr = (hash & (1LL << 32) - 1);
            hashr = ((hashr - curh2 * str[i + j]) % MOD2 + MOD2) % MOD2;
            hashr = (hashr + curh2 * '?') % MOD2;

            ll hashlr = (hashl << 32) | hashr;
            auto it2 = bucket.find(hashlr);
            if(it2 == bucket.end()) {
                it2 = bucket.insert({ hashlr, 0 }).first;
            }
            res[k] += it2->second;
            it2->second++;

            curh = (curh * h) % MOD;
            curh2 = (curh2 * h2) % MOD2;
        }

        auto it = bucket.find(hash);
        if(it == bucket.end()) it = bucket.insert({ hash, 0 }).first;
        res[k] -= it->second * (k - 1);
        it->second++;
    }
}

hash_set<ll> p2bucket;
ll curh = 1;
ll curh2 = 1;
void addh()
{
    for(char c1 = 'a'; c1 <= 'z'; ++c1) {
        for(char c2 = 'a'; c2 <= 'z'; ++c2) {
            ll h1l = curh * c1 % MOD;
            ll h1r = curh2 * c1 % MOD2;
            ll h2l = curh * c2 % MOD;
            ll h2r = curh2 * c2 % MOD2;
            ll gapl = ((h1l - h2l) % MOD + MOD) % MOD;
            ll gapr = ((h1r - h2r) % MOD2 + MOD2) % MOD2;
            p2bucket.insert((gapl << 32) | gapr);
        }
    }
    curh = (curh * h) % MOD;
    curh2 = (curh2 * h2) % MOD2;
}

void p2(int k)
{
    addh();

    for(int i = 0; i + k - 1 < n; i += k) {
        for(int j = i + k; j + k - 1 < n; j += k) {
            ll hash1 = sh.substr(i, i + k - 1);
            ll hash2 = sh.substr(j, j + k - 1);

            ll h1l = hash1 >> 32;
            ll h1r = hash1 & ((1ll << 32) - 1);
            ll h2l = hash2 >> 32;
            ll h2r = hash2 & ((1ll << 32) - 1);

            ll gapl = ((h1l - h2l) % MOD + MOD) % MOD;
            ll gapr = ((h1r - h2r) % MOD2 + MOD2) % MOD2;
            auto it = p2bucket.find((gapl << 32) | gapr);
            if(it != p2bucket.end()) res[k]++;
        }
    }
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;

    sh.build(str);

    int nsq = (int)sqrt(n);
    for(int i = 1; i <= n; ++i) {
        // cout << i << "\n";
        if(i <= 200) {
            p1(i);
            addh();
        } else p2(i);
        if(n / i <= 1) break;
    }

    for(int i = 1; i <= n; ++i) {
        cout << res[i] << " ";
    }

    return 0;
}
