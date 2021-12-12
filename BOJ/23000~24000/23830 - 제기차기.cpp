#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;


int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a)cin >> v;
    int p, q, r;
    ll s;
    cin >> p >> q >> r >> s;

    auto ck = [&](int k) {
        ll res = 0;
        for(int v : a) {
            if(v > k + r) v -= p;
            else if(v < k) v += q;
            res += v;
        }

        return res;
    };

    int lo = 0, hi = 100011;
    while(lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if(ck(m) < s) {
            lo = m;
        } else {
            hi = m;
        }
    }

    if(hi == 100011) hi = -1;
    cout << hi;

    return 0;
}
