#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

using ll = long long int;

constexpr ll b0 = 3137;
constexpr ll p0 = 998244353;
constexpr ll b1 = 53;
constexpr ll p1 = 1610612741;

struct RollHash
{
    ll h0, h1;
    ll h0max, h1max;

    RollHash()
    {
        h0 = 0;
        h1 = 0;
        h0max = 1;
        h1max = 1;
    }

    void addChar(char c)
    {
        h0 = (h0 * b0 + c) % p0;
        h1 = (h1 * b1 + c) % p1;
        h0max = (h0max * b0) % p0;
        h1max = (h1max * b1) % p1;
    }

    void removeAndAddChar(char rmc, char addc)
    {
        h0 = (h0 * b0) % p0;
        h1 = (h1 * b1) % p1;
        h0 = (h0 - (h0max * rmc) % p0 + p0) % p0;
        h1 = (h1 - (h1max * rmc) % p1 + p1) % p1;
        h0 = (h0 + addc) % p0;
        h1 = (h1 + addc) % p1;
    }

    ll get()
    {
        return (h0 << 32) | h1;
    }
};

bool operator<(const RollHash& l, const RollHash& r)
{
    if(l.h0 != r.h0) return l.h0 < r.h0;
    return l.h1 < r.h1;
}

bool operator==(const RollHash& l, const RollHash& r)
{
    if(l.h0 != r.h0) return false;
    if(l.h1 != r.h1) return false;
    return true;
}
bool operator!=(const RollHash& l, const RollHash& r)
{
    return !(l == r);
}

template <ll h = 3137, ll m = 998244353, ll h2 = 53, ll m2 = 1610612741>
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

        hv[0] = str[0];
        hpow[0] = 1;
        for(int i = 1; i < n; ++i) {
            hv[i] = (hv[i - 1] * h + str[i]) % m;
            hpow[i] = (hpow[i - 1] * h) % m;
        }

        hv2.resize(n);
        hpow2.resize(n);

        hv2[0] = str[0];
        hpow2[0] = 1;
        for(int i = 1; i < n; ++i) {
            hv2[i] = (hv2[i - 1] * h2 + str[i]) % m2;
            hpow2[i] = (hpow2[i - 1] * h2) % m2;
        }
    }

    // [l, r]
    ll substr(int l, int r)
    {
        ll res = hv[r];
        if(l > 0) {
            res -= hv[l - 1] * hpow[r - l + 1];
            res = ((res % m) + m) % m;
        }
        ll res2 = hv2[r];
        if(l > 0) {
            res2 -= hv2[l - 1] * hpow2[r - l + 1];
            res2 = ((res2 % m2) + m2) % m2;
        }
        return (res << 32) | res2;
    }
};

struct Node
{
    int len;
    int cnt;
};

int n, m;
string d[100001], str;
StrHash strhs;
RollHash dhs[100001], dhs2[100001];
vector<Node> prenum, sufnum;
unordered_set<ll> hashes;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
        RollHash hs;
        for(int j = 0; j < d[i].size(); ++j) {
            hs.addChar(d[i][j]);
        }
        hashes.insert(hs.get());
    }
    cin >> str;
    m = str.size();
    strhs.build(str);

    sort(d, d + n, [](const string& l, const string& r) {
        return l.size() < r.size();
    });
    for(int i = 0; i < n; ++i) {
        RollHash hs;
        for(int j = 0; j < d[i].size(); ++j) {
            hs.addChar(d[i][j]);
        }
        dhs[i] = hs;

        hs = RollHash();
        for(int j = d[i].size() - 1; j >= 0; --j) {
            hs.addChar(d[i][j]);
        }
        dhs2[i] = hs;
    }

    int sz = 0;
    RollHash rh;
    for(int i = 0; i < n; ++i) {
        while(sz < d[i].size() && sz < str.size()) {
            rh.addChar(str[sz]);
            sz++;
        }
        if(sz == str.size()) break;
        if(rh == dhs[i]) {
            if(prenum.size() == 0 || prenum.back().len != sz) {
                prenum.push_back({ sz, 0 });
            }
            prenum.back().cnt++;
        }
    }
    sz = 0;
    rh = RollHash();
    for(int i = 0; i < n; ++i) {
        while(sz < d[i].size() && sz < str.size()) {
            rh.addChar(str[m - sz - 1]);
            sz++;
        }
        if(sz == str.size()) break;
        if(rh == dhs2[i]) {
            if(sufnum.size() == 0 || sufnum.back().len != sz) {
                sufnum.push_back({ sz, 0 });
            }
            sufnum.back().cnt++;
        }
    }

    ll res = 0;
    for(auto& pp : prenum) {
        for(auto& ss : sufnum) {
            if(pp.len + ss.len + 1 > m) break;
            ll hs = strhs.substr(pp.len, m - ss.len - 1);

            auto it = hashes.find(hs);
            if(it != hashes.end()) {
                res += pp.cnt * ss.cnt;
            }
        }
    }

    cout << res;

    return 0;
}
