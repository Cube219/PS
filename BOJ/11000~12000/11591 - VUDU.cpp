#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_DECLARE_NONSTDC_NAMES 0 // for using y1 as variable name

#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long int;

ll n, a[1000001], p;
vector<ll> tmp;

ll process(int l, int r)
{
    if(l == r) {
        if(a[l] >= 0) return 1;
        else return 0;
    }

    int m = (l + r) / 2;
    ll ret = 0;
    ret += process(l, m);
    ret += process(m + 1, r);

    tmp.clear();
    tmp.push_back(a[m + 1]);
    for(int i = m + 2; i <= r; ++i) {
        tmp.push_back(tmp.back() + a[i]);
    }
    sort(tmp.begin(), tmp.end());
    ll curSum = 0;
    for(int i = m; i >= l; --i) {
        curSum += a[i];
        ret += tmp.end() - lower_bound(tmp.begin(), tmp.end(), -curSum);
    }
    return ret;
}

int main(void)
{
#ifdef CUBE_PS
    freopen("input.txt", "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> p;
    for(int i = 0; i < n; ++i) {
        a[i] -= p;
    }

    cout << process(0, n - 1);

    return 0;
}
