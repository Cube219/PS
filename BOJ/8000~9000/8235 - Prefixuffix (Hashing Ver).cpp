#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

template <ll h = 3137, ll m = 998244353>
struct StrHash
{
    vector<ll> hv;
    vector<ll> hpow;

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
    }

    // [l, r]
    ll substr(int l, int r)
    {
        ll res = hv[r];
        if(l > 0) {
            res -= hv[l - 1] * hpow[r - l + 1];
            res = ((res % m) + m) % m;
        }
        return res;
    }
};

StrHash hs;
int n;
string str;

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> str;
    hs.build(str);

    int res = 0;
    int bsz = 0;
    for(int asz = n / 2; asz >= 1; --asz) {
        bsz = min(bsz + 2, n / 2 - asz);

        if(hs.substr(0, asz - 1) != hs.substr(n - asz, n - 1)) continue;
        while(bsz > 0 && hs.substr(asz, asz + bsz - 1) != hs.substr(n - asz - bsz, n - asz - 1)) bsz--;
        res = max(res, asz + bsz);
    }

    cout << res;

    return 0;
}
