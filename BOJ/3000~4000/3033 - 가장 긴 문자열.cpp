#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cassert>
#include <vector>
#include <set>
using namespace std;

using ll = long long int;

struct RollHash
{
    ll b0 = 3137;
    ll p0 = 1000003;
    ll b1 = 53;
    ll p1 = 1100023;

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


int n;
char str[200002];
bool buk[1000003];
vector<int> buk2[1100023];

bool ck(int l)
{
    int num = 0;
    for(int i = 0; i < 1000003; ++i) {
        buk[i] = false;
    }
    for(int i = 0; i < 1100023; ++i) {
        buk2[i].clear();
    }
    RollHash h;
    for(int i = 0; i < l; ++i) {
        h.addChar(str[i]);
    }
    buk[h.h0] = true;
    buk2[h.h1].push_back(h.h0);
    for(int i = l; i < n; ++i) {
        h.removeAndAddChar(str[i - l], str[i]);
        if(buk[h.h0] == true) {
            for(int j = 0; j < buk2[h.h1].size(); ++j) {
                if(buk2[h.h1][j] == h.h0) {
                    return true;
                }
            }
        }
        buk[h.h0] = true;
        buk2[h.h1].push_back(h.h0);
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

    cin >> n >> str;
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
    