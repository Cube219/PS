#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

using ll = long long int;

constexpr ll b0 = 1000001;
constexpr ll p0 = 1000000007;
constexpr ll b1 = 1000003;
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

    void addChar(int c)
    {
        h0 = (h0 * b0 + c) % p0;
        h1 = (h1 * b1 + c) % p1;
        h0max = (h0max * b0) % p0;
        h1max = (h1max * b1) % p1;
    }

    void removeAndAddChar(int rmc, int addc)
    {
        h0 = (h0 * b0) % p0;
        h1 = (h1 * b1) % p1;
        h0 = (h0 - (h0max * rmc) % p0 + p0) % p0;
        h1 = (h1 - (h1max * rmc) % p1 + p1) % p1;
        h0 = (h0 + addc) % p0;
        h1 = (h1 + addc) % p1;
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

int n, k;
int d[20001];
map<pair<ll, ll>, int> mp;

bool ck(int len)
{
    mp.clear();
    RollHash rh;
    for(int i = 0; i < len; ++i) {
        rh.addChar(d[i]);
    }
    mp.insert({ { rh.h0, rh.h1 }, 1 });
    for(int i = len; i < n; ++i) {
        rh.removeAndAddChar(d[i - len], d[i]);
        auto it = mp.find({ rh.h0, rh.h1 });
        if(it == mp.end()) {
            it = mp.insert({ {rh.h0, rh.h1}, 0 }).first;
        }
        it->second++;
    }

    for(auto& it : mp) {
        if(it.second >= k) return true;
    }
    return false;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    for(int i = 0; i < n; ++i) {
        cin >> d[i];
    }

    int l = 0, r = n;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        if(ck(m) == true) {
            l = m;
        } else {
            r = m;
        }
    }

    cout << l;

    return 0;
}
