#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

int n, d;
vector<int> t, v;
ll res;

void dnq(int s, int e, int jmin, int jmax)
{
    if(s > e) return;

    int m = (s + e) / 2;

    int jmin2 = max(jmin, m);
    int jmax2 = min(jmax, m + d);
    int jmid = -1;
    ll r = 0;
    for(int j = jmin2; j <= jmax2; ++j) {
        ll tmp = (ll)(j - m) * t[j] + v[m];
        if(tmp > r) {
            r = tmp;
            jmid = j;
        }
    }
    res = max(res, r);
    dnq(s, m - 1, jmin, jmid);
    dnq(m + 1, e, jmid, jmax);
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> d;
    t.resize(n); v.resize(n);
    for(auto& a : t) cin >> a;
    for(auto& a : v) cin >> a;

    dnq(0, n - 1, 0, n - 1);

    cout << res;

    return 0;
}
