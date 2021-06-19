#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

using ll = long long int;

constexpr ll b0 = 3137;
constexpr ll p0 = 1000003;
constexpr ll b1 = 53;
constexpr ll p1 = 1100023;

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

bool buk[p0];
vector<pair<int, int>> buk2[p1];

void clearbucket()
{
    for(int i = 0; i < p0; ++i) {
        buk[i] = false;
    }
    for(int i = 0; i < p1; ++i) {
        buk2[i].clear();
    }
}

void addBucket(RollHash& h)
{
    buk[h.h0] = true;
    for(int i = 0; i < buk2[h.h1].size(); ++i) {
        if(buk2[h.h1][i].first == h.h0) {
            buk2[h.h1][i].second++;
            return;
        }
    }
    buk2[h.h1].push_back({ h.h0, 1 });
}

int hasBucket(RollHash& h)
{
    if(buk[h.h0] == true) {
        for(int j = 0; j < buk2[h.h1].size(); ++j) {
            if(buk2[h.h1][j].first == h.h0) {
                return buk2[h.h1][j].second;
            }
        }
    }
    return 0;
}

string str;
int n;

bool ck(int k)
{
    clearbucket();
    RollHash hs;

    for(int i = 0; i < k; ++i) {
        hs.addChar(str[i]);
    }
    addBucket(hs);
    for(int i = k; i < n; ++i) {
        hs.removeAndAddChar(str[i - k], str[i]);
        addBucket(hs);
    }

    RollHash hs2;
    for(int i = 0; i < k; ++i) {
        hs2.addChar(str[i]);
    }
    if(hasBucket(hs2) == 1) return true;
    for(int i = k; i < n; ++i) {
        hs2.removeAndAddChar(str[i - k], str[i]);
        if(hasBucket(hs2) == 1) return true;
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

    cin >> str;
    n = str.size();
    int l = 0, r = n;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        if(ck(m) == true) {
            r = m;
        } else {
            l = m;
        }
    }

    clearbucket();
    RollHash hs;

    for(int i = 0; i < r; ++i) {
        hs.addChar(str[i]);
    }
    addBucket(hs);
    for(int i = r; i < n; ++i) {
        hs.removeAndAddChar(str[i - r], str[i]);
        addBucket(hs);
    }

    RollHash hs2;
    for(int i = 0; i < r; ++i) {
        hs2.addChar(str[i]);
    }
    if(hasBucket(hs2) == 1) {
        cout << str.substr(0, r);
        return 0;
    }
    for(int i = r; i < n; ++i) {
        hs2.removeAndAddChar(str[i - r], str[i]);
        if(hasBucket(hs2) == 1) {
            cout << str.substr(i - r + 1, r);
            break;
        }
    }

    return 0;
}
